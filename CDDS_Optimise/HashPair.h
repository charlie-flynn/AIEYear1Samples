#pragma once

struct HashPair
{
public:
	unsigned int key;
	unsigned char* value;
	unsigned int hashed;

	HashPair();
	HashPair(unsigned int key, unsigned char* value, unsigned int hashed);
	~HashPair() = default;
};



