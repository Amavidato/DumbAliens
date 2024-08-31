#include "EnemyMovementSystem.h"

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../Game.h"
#include "../settings/EnemySettings.h"

void EnemyMovementSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<EnemyTag, Position2D, Direction2D, Speed>();
}

void EnemyMovementSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	auto firstEntity = *entities.begin();
	auto pos = ecsManager->GetComponent<Position2D>(firstEntity);
	auto& direction = ecsManager->GetComponent<Direction2D>(firstEntity);
	auto speed = ecsManager->GetComponent<Speed>(firstEntity);
	std::pair<float,float> movement{};
	if(direction.x != 0)
	{
		movement.first = static_cast<float>(direction.x * speed.value) * deltaTime;
		if(direction.x > 0 &&
			pos.x < EnemySettings::enemiesMaxHorizontalDistance &&
			pos.x + movement.first > EnemySettings::enemiesMaxHorizontalDistance)
		{
			movement.first = EnemySettings::enemiesMaxHorizontalDistance - pos.x;
			direction.x = 0;
			direction.y = 1;
		}
		else if(direction.x < 0 &&
			pos.x > 0 &&
			pos.x + movement.first < 0)
		{
			movement.first = 0 - pos.x;
			direction.x = 0;
			direction.y = 1;
		}
	}
	else if (direction.y != 0)
	{
		movement.second = static_cast<float>(direction.y * EnemySettings::enemyHeight);
		if(pos.y < EnemySettings::enemiesMaxVerticalDistance &&
			pos.y + movement.second > EnemySettings::enemiesMaxVerticalDistance)
		{
			SystemManager::STOP_SYSTEMS_EXECUTION = true;
			return;
		}
		direction.x = pos.x == 0.0 ? 1 : -1;
		direction.y = 0;
	}
	for (auto entity : entities)
	{
		auto& position = ecsManager->GetComponent<Position2D>(entity);
		position.x += movement.first;
		position.y += movement.second;
	}
}
