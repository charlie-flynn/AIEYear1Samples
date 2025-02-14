#include "Critter.h"


Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isLoaded = false;
	m_isInitialized = false;
	m_textureID = 0;
}

Critter::~Critter()
{
	m_isLoaded = false;
}

const bool Critter::operator==(const Critter& other) const
{
	return m_position.x == other.m_position.x &&
		m_position.y == other.m_position.y &&
		m_velocity.x == other.m_velocity.x &&
		m_velocity.y == other.m_velocity.y &&
		m_radius == other.m_radius;
}

const bool Critter::operator!=(const Critter& other) const
{
	return !(*this == other);
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, const char* texture)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	m_textureName = (char*)texture;
	
	//if (!m_isInitialized)
	//	m_texture = LoadTexture(texture);

	m_isInitialized = true;
}

void Critter::Unload()
{
	m_position = { 9999, 9999 };
	m_isLoaded = false;
}

void Critter::Destroy()
{
	//UnloadTexture(m_texture);
}

void Critter::Update(float dt)
{
	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}


void Critter::Draw()
{
	//DrawTexture(m_texture, m_position.x - m_radius, m_position.y - m_radius, WHITE);
}
