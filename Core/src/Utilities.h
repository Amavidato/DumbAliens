#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H
#include "Components.h"
#include "../ecs_core/EcsManager.h"

namespace utils
{
	static bool IsThereACollision(Collider2D collider1, Position2D position1, Collider2D collider2, Position2D position2)
	{
		return position1.x + collider1.width > position2.x &&
				position1.y + collider1.height > position2.y &&
				position2.x + collider2.width > position1.x &&
				position2.y + collider2.height > position1.y;
	}

	static bool IsThereACollision(Entity e1, Entity e2, EcsManager* ecsManager)
	{
		auto collider1 = ecsManager->GetComponent<Collider2D>(e1);
		auto position1 = ecsManager->GetComponent<Position2D>(e1);
		auto collider2 = ecsManager->GetComponent<Collider2D>(e2);
		auto position2 = ecsManager->GetComponent<Position2D>(e2);
		return IsThereACollision(collider1, position1, collider2, position2);
	}
	
	static int Sign(int number)
	{
		if (number > 0) return 1;
		if (number < 0) return -1;
		return 0;
	}

	static int Sign(float number)
	{
		if (number > 0) return 1;
		if (number < 0) return -1;
		return 0;
	}

}

#endif // UTILITIES_H