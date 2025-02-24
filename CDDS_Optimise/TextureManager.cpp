#include "TextureManager.h"
#include "Critter.h"
#include "HashTable.h"
#include "raylib.h"

TextureManager::TextureManager(int length) : m_textureNames(HashTable(length))
{
	//m_textureNames = HashTable(length);
	m_textures = new Texture2D[length];
	m_count = 0;
	m_length = length;

	for (int i = 0; i < m_length; i++)
	{
		m_textures[i] = Texture2D();
	}
}

TextureManager::~TextureManager()
{
	delete[] m_textures;
}

void TextureManager::TextureLoad(const char* name)
{
	if (m_textureNames.Add(name))
	{
		m_length = m_textureNames.GetArrayLength();
		m_textures[m_textureNames.Hash((unsigned char*)name) % m_length] = LoadTexture(name);
		m_count++;
	}
		
}

Texture2D* TextureManager::GetTexture(const char* name)
{
	if (m_textureNames.Contains((char*)name))
	{
		return &m_textures[m_textureNames.Hash((unsigned char*)name) % m_length];
	}
}

