#pragma once
#include "List.h"
#include "Critter.h"

class ObjectPool
{
public:
	List<Critter> objects;
private:
	int m_activeCount;
	int m_inactiveCount;
public:
	ObjectPool();
	~ObjectPool();
	void Allocate(Vector2 position, Vector2 velocity, float radius, const char* texture);
	void Deallocate(Critter& critter);
	const int GetActiveCount() const { return m_activeCount; }
	int GetInactiveCount() { return m_inactiveCount; }
};