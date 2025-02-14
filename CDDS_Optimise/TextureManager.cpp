#include "TextureManager.h"
#include "Critter.h"
#include "HashTable.h"
#include "raylib.h"

TextureManager::TextureManager(int length)
{
	m_textureNames = HashTable(length);
	m_textures = new Texture2D[length];
	m_count = 0;
	m_length = length;

	for (int i = 0; i < m_length; i++)
	{
		m_textures[i] = Texture2D();
	}
}

void TextureManager::NotRaylibLoadTexture(const char* texture)
{
	if (m_textureNames.Add(texture))
	{
		if (int index = FindEmptyIndex((char*)texture) >= 0)
			m_textures[index] = LoadTexture(texture);
	}
}

void TextureManager::Draw(Critter* critter)
{
	if (m_textureNames.Contains(critter->GetTextureName()))
	{
		
	}
}

// returns -1 if it fails
int TextureManager::FindEmptyIndex(char* name)
{
	int index = m_textureNames.Hash((unsigned char*)name) % m_length;

	for (int i = 0; i < m_length; i++)
	{
		if (m_textures[index].width = 0)
			return index;
		else
			index = (index + 1) % m_length;
	}

	return -1;
}
