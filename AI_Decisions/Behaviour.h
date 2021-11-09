#pragma once
namespace pathfinding
{
	class Agent;

	// abstract base class for all actions
	class Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltaTime) = 0;
	};
}