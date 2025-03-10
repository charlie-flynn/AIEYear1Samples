#pragma once
#include "List.h"
#include "Critter.h"

class CritterPool
{
public:
	List<Critter> objects;
private:
	int m_activeCount;
	int m_inactiveCount;
public:
	CritterPool();
	~CritterPool();
	void Load(Vector2 position, Vector2 velocity, float radius);
	bool Unload(Critter& critter);
	void AddCritter();
	void RemoveCritter();
	const int GetActiveCount() const { return m_activeCount; }
	int GetInactiveCount() { return m_inactiveCount; }
};