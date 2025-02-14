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

void TextureManager::TextureLoad(const char* name)
{
	if (m_textureNames.Add(name))
	{
		m_textures[m_count] = LoadTexture(name);
		m_count++;
	}
		
}

void TextureManager::Draw(Critter* critter)
{
	if (m_textureNames.Contains(critter->GetTextureName()))
	{
		DrawTexture(m_textures[critter->GetTextureID()], critter->GetX() - critter->GetRadius(), critter->GetY() - critter->GetRadius(), WHITE);
	}
}

