#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	m_activeCount = 0;
	m_inactiveCount = 0;
	objects = List<Critter>();
}

ObjectPool::~ObjectPool()
{
	objects.Destroy();
}

void ObjectPool::Allocate(Vector2 position, Vector2 velocity, float radius, const char* texture)
{
	if (m_inactiveCount <= 0)
	{
		objects.PushFront(Critter());
		objects.First().Init(position, velocity, radius, texture);
		m_activeCount++;
		return;
	}
	
	objects.PushFront(objects.PopBack());
	objects.First().Init(position, velocity, radius, texture);
	m_activeCount++;
	m_inactiveCount--;
}

void ObjectPool::Deallocate(Critter& critter)
{
	if (m_activeCount <= 0)
		return;

	Critter alsoCritter = critter;

	critter.Unload();
	objects.Remove(critter);
	objects.PushBack(alsoCritter);
	m_activeCount--;
	m_inactiveCount++;
}
