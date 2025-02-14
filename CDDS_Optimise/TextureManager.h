#pragma once
#include "HashTable.h"

class Texture2D;

class Critter;

class TextureManager
{
private:
	HashTable m_textureNames;
	Texture2D* m_textures;
	int m_count;
	int m_length;

public:
	TextureManager(int length = 100);

	void TextureLoad(const char* name);
	void Draw(Critter* critter);
};