#pragma once


#include "raylib.h"

class Critter
{
protected:	
	Vector2 m_position;
	Vector2 m_velocity;
	float m_radius;

	char* m_textureName;
	int m_textureID;

	bool m_isLoaded;
	bool m_isDirty;		// indicates if we've already processed a collision response for this critter
	bool m_isInitialized;
	
public:
	Critter();
	~Critter();
	const bool operator==(const Critter& other) const;
	const bool operator!=(const Critter& other) const;

	void Init(Vector2 position, Vector2 velocity, float radius, const char* texture);
	void Unload();
	void Destroy();
	void Update(float dt);

	[[deprecated("TextureManager now handles drawing textures to the screen")]]
	void Draw();

	float GetX() { return m_position.x; }
	float GetY() { return m_position.y; }
	void SetX(float x) { m_position.x = x; }
	void SetY(float y) { m_position.y = y; }

	Vector2 GetPosition() { return m_position; }
	void SetPosition(Vector2 position) { m_position = position; }

	Vector2 GetVelocity() { return m_velocity; }
	void SetVelocity(Vector2 velocity) { m_velocity = velocity; }

	float GetRadius() { return m_radius; }

	char* GetTextureName() { return m_textureName; }

	int GetTextureID() { return m_textureID; }
	void SetTextureID(int value) { m_textureID = value; }

	bool IsDirty() { return m_isDirty; }
	void SetDirty() { m_isDirty = true; }

	[[deprecated("m_isLoaded was replaced by moving the critter to the back of the CritterPool")]]
	bool IsDead() { return m_isLoaded == false; }

};

