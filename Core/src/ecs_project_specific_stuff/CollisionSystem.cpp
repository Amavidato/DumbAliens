#include "CollisionSystem.h"

#include <iostream>

#include "Components.h"
#include "../Utilities.h"
#include "../ecs_core/EcsManager.h"

void CollisionSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Collider2D>();
}

void CollisionSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	std::vector entitiesCopy (entities.begin(), entities.end());
	for (int i = 0; i < entities.size()-1; i++)
	{
		for (int j = i+1; j < entities.size(); j++)
		{
			if(utils::IsThereACollision(entitiesCopy[i], entitiesCopy[j], ecsManager))
			{
				std::cout << "Collision detected between Entities:"<<entitiesCopy[i]<<" and "<<entitiesCopy[j]<<std::endl;
			}
		}
	}
}