#include "CritterPool.h"

CritterPool::CritterPool()
{
	m_activeCount = 0;
	m_inactiveCount = 0;
	objects = List<Critter>();
}

CritterPool::~CritterPool()
{
	objects.Destroy();
}

void CritterPool::Load(Vector2 position, Vector2 velocity, float radius, const char* texture)
{
	if (m_inactiveCount <= 0)
	{
		objects.PushFront(Critter());
		objects.First().Init(position, velocity, radius, texture);
		m_activeCount++;
	}
	else
	{
		objects.PushFront(objects.PopBack());
		objects.First().Init(position, velocity, radius, texture);
		m_activeCount++;
		m_inactiveCount--;
	}
}

bool CritterPool::Unload(Critter& critter)
{
	if (m_activeCount <= 0)
		return false;

	Critter pushBackCritter = critter;
	bool isRemoved;

	if (isRemoved = objects.Remove(critter))
	{
		objects.PushBack(pushBackCritter);
		m_activeCount--;
		m_inactiveCount++;
	}

	return isRemoved;
}
