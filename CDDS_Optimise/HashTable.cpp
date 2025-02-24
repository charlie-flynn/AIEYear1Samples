#include "HashTable.h"
#include <string>

// Creates an empty hash table of the given size.
HashTable::HashTable(int size)
{
    m_count = 0;
    m_arrayLength = size;
    m_values = new HashPair[m_arrayLength];

    // initialize the array
    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }
}

// Creates a hash table of twice the length of the given initializer list, with the given contents inside.
HashTable::HashTable(std::initializer_list<const char*> values)
{
    m_count = 0;
    m_arrayLength = values.size() * 2;
    m_values = new HashPair[m_arrayLength];

    // initialize the array, then add the values to it
    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }
    for (const char* value : values)
    {
        Add(value);
    }
}

// Creates a hash table of twice the length of the given character pointer array, with the given contents inside.
HashTable::HashTable(char* values[], int length)
{
    m_count = 0;
    m_arrayLength = length * 2;
    m_values = new HashPair[m_arrayLength];

    // initialize the array, then add the values to it
    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    for (int i = 0; i < length; i++)
    {
        Add(values[i]);
    }
}

HashTable::~HashTable()
{
    delete[] m_values;
    m_values = nullptr;
}

// Returns a reference to the given value, or nullptr if it isn't in the table.
unsigned char*& HashTable::operator[](const char* key)
{
    unsigned int hashed = Hash((unsigned char*)key);
    unsigned int keyAsIndex = hashed % m_arrayLength;
    unsigned int index = keyAsIndex;
    int numberSearched = 0;

    for (int i = 0; i < m_arrayLength && m_values[index].hashed != 0; i++)
    {
        if (m_values[index].hashed == hashed)
        {
            return m_values[index].value;
        }

        index = (index + 1) % m_arrayLength;
        numberSearched++;
    }

    unsigned char* nullPointer = nullptr;
    return nullPointer;
}

// Adds the given value to the hash table, and returns whether it was successful or not.
bool HashTable::Add(const char* value)
{
    if (value == nullptr || m_count >= m_arrayLength)
        return false;

    // get the value hashed and store that and the value modulated to the array's size for later
    unsigned int hashed = Hash((unsigned char*)value);
    unsigned int key = hashed % m_arrayLength;
    unsigned int index = key;
    int numberSearched = 0;

    for (int i = 0; i < m_arrayLength && m_values[index].hashed != hashed; i++)
    {
        if (m_values[index].hashed == 0)
        {
            m_values[index] = HashPair(key, (unsigned char*)value, hashed);
            m_count++;

            // if count is greater than or equal to two-thirds the array length, double the array length
            if (m_count >= m_arrayLength - (m_arrayLength / 3))
                Resize(m_arrayLength * 2);

            return true;
        }
        else
        {
            index = (index + 1) % m_arrayLength;
            numberSearched++;
        }
    }

    return false;
}

// Removes the given value to the hash table, and returns whether it was successful or not.
bool HashTable::Remove(const char* value)
{
    if (value == nullptr)
        return false;

    unsigned int hashed = Hash((unsigned char*)value);
    unsigned int key = hashed % m_arrayLength;
    unsigned int index = key;

    // find the value, replace it with a empty hashpair decrement the count and return true if it's found. otherwise return false
    for (int i = 0; i < m_arrayLength; i++)
    {
        if (m_values[index].hashed != 0)
        {
            if (m_values[index].hashed == hashed)
            {
                m_values[index] = HashPair();
                m_count--;
                return true;
            }
        }

        index = (index + 1) % m_arrayLength;
    }

    return false;
}

// Resizes the hash table to the given size.
bool HashTable::Resize(int size)
{
    // guard clause
    if (size == m_arrayLength || size <= 0 || size < m_count)
        return false;

    int copiedCount = 0;

    // make a new array, and intialize all the values
    HashPair* newValues = new HashPair[size];

    for (int i = 0; i < size; i++)
    {
        newValues[i] = HashPair();
    }

    for (int i = 0; i < m_arrayLength; i++)
    {
        // if there is a value in the given index in the old array, rehash it and copy it over to the new array
        if (m_values[i].hashed != 0)
        {
            int j = Hash(m_values[i].value) % size;
            while (true)
            {
                if (newValues[j].hashed == 0)
                {
                    newValues[j] = HashPair(Hash(m_values[i].value) % size, m_values[i].value, m_values[i].hashed);
                    break;
                }
                else
                {
                    j = (j + 1) % size;
                }
            }
        }
    }

    // delete the old values and copy over the new values
    delete[] m_values;
    m_values = newValues;
    m_arrayLength = size;
}

// Returns true if the given value is contained in the hash table.
bool HashTable::Contains(char* value)
{
    return this->operator[](value) != nullptr;
}

// Hashes the given character pointer using ELF hash.
unsigned int HashTable::Hash(unsigned char* value)
{
    int length = ((std::string)(char*)value).length();
    unsigned int hash = 0, x = 0;
    for (int i = 0; i < length; i++)
    {
        hash = (hash << 4) + value[i];
        if ((x = hash & 0xF0000000L) != 0) 
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return (hash & 0x7FFFFFFF);
}

// Clears the entire array, and reinitalizes it.
void HashTable::Clear()
{
    delete[] m_values;
    m_values = new HashPair[m_arrayLength];

    for (int i = 0; i < m_arrayLength; i++)
    {
        m_values[i] = HashPair();
    }

    m_count = 0;
}
