#pragma once
#include "HashTable.h"
#include "Critter.h"

class Texture2D;

class TextureManager
{
private:
	HashTable m_textureNames;
	Texture2D* m_textures;
	int m_count;
	int m_length;

public:
	TextureManager(int length = 100);

	void NotRaylibLoadTexture(const char* texture);
	void Draw(Critter* critter);
	int FindEmptyIndex(char* name);
};