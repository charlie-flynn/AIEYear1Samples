#include "HashPair.h"

HashPair::HashPair() : key(0), value(nullptr), hashed(0)
{
}

HashPair::HashPair(unsigned int key, unsigned char* value, unsigned int hashed) : key(key), value((unsigned char*)value), hashed(hashed)
{
}
