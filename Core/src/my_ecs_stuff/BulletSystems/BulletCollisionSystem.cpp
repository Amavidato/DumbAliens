#include "BulletCollisionSystem.h"

#include "../Components.h"
#include "../../Utilities.h"
#include "../../ecs_core/EcsManager.h"
#include "../../ecs_core/commandBuffer/EcsCommandBuffer.h"
#include "../../Game.h"

void BulletCollisionSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<BulletTag>();
}

void BulletCollisionSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	EcsCommandBuffer* ecb = new EcsCommandBuffer(std::shared_ptr<EcsManager>(ecsManager));
	std::unordered_set<Entity> enemies = ecsManager->GetEntitiesWithAny<EnemyTag>();
	bool hit = false;
	for (auto bulletIterator = entities.begin(); bulletIterator != entities.end(); )
	{
		for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end(); )
		{
			if(utils::IsThereACollision(*bulletIterator, *enemyIterator, ecsManager))
        	{
 				ecb->DestroyEntity(*bulletIterator);
 				ecb->DestroyEntity(*enemyIterator);
				enemies.erase(enemyIterator);
				hit = true;
				Game::SCORE += 10;
				break;
        	}
			++enemyIterator;
		}
		if(hit)
		{
			hit = false;
			++bulletIterator;
		}
		else
		{
			++bulletIterator;
		}
	}
	ecb->Execute();
}
