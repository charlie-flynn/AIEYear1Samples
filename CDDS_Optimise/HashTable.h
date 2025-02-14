#pragma once
#include "HashPair.h"
#include <initializer_list>

class HashTable
{
private:
	HashPair* m_values;
	int m_count;
	int m_arrayLength;
public:
	HashTable(int size = 100);
	HashTable(std::initializer_list<const char*> values);
	HashTable(char* values[], int length);
	~HashTable();
	unsigned char*& operator[](const char* key);
	bool Add(const char* value);
	bool Remove(const char* value);
	void Resize(int size);
	bool Contains(char* value);
	int GetCount() { return m_count; };
	int GetArrayLength() { return m_arrayLength; };
	unsigned int Hash(unsigned char* value);
	void Clear();
};