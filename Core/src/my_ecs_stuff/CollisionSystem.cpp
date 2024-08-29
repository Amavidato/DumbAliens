#include "CollisionSystem.h"

#include <iostream>

#include "Components.h"
#include "../ecs_core/EcsManager.h"

void CollisionSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Collider2D>();
}

void CollisionSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	std::vector<Entity> entitiesCopy (entities.begin(), entities.end());
	for (int i = 0; i < entities.size()-1; i++)
	{
		for (int j = i+1; j < entities.size(); j++)
		{
			if(IsThereACollision(entitiesCopy[i], entitiesCopy[j], ecsManager))
			{
				std::cout << "Collision detected between Entities:"<<entitiesCopy[i]<<" and "<<entitiesCopy[j]<<std::endl;
			}
		}
	}
}

bool CollisionSystem::IsThereACollision(Entity entity1, Entity entity2, EcsManager* ecsManager)
{
	auto& collider1 = ecsManager->GetComponent<Collider2D>(entity1);
	auto& position1 = ecsManager->GetComponent<Position2D>(entity1);
	auto& collider2 = ecsManager->GetComponent<Collider2D>(entity2);
	auto& position2 = ecsManager->GetComponent<Position2D>(entity2);
	return position1.x + collider1.width > position2.x &&
			position1.y + collider1.height > position2.y &&
			position2.x + collider2.width > position1.x &&
			position2.y + collider2.height > position1.y;
				;
}
