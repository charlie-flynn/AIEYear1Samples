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
		objects.PushFront(Critter());
	else
		objects.PushFront(objects.PopBack());

	objects.First().Init(position, velocity, radius, texture);
	m_activeCount++;
	m_inactiveCount--;
}

void ObjectPool::Deallocate(Critter& critter)
{
	if (m_activeCount <= 0)
		return;

	objects.PushBack(critter);
	objects.Remove(critter);
	m_activeCount--;
	m_inactiveCount++;
}
