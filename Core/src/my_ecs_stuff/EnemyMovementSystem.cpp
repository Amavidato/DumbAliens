#include "EnemyMovementSystem.h"

#include "Components.h"
#include "../Utilities.h"
#include "../ecs_core/EcsManager.h"
#include "../settings/EnemySettings.h"

void EnemyMovementSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<EnemyTag, Position2D, Direction2D, Speed>();
}

void EnemyMovementSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for (auto entity : entities)
	{
		auto& position = ecsManager->GetComponent<Position2D>(entity);
		auto& distanceTravelled = ecsManager->GetComponent<DistanceTravelled>(entity);
		auto& direction = ecsManager->GetComponent<Direction2D>(entity);
		auto speed = ecsManager->GetComponent<Speed>(entity);
		auto startingPosX = ecsManager->GetComponent<StartingPositionX>(entity);
		std::pair<float,float> movement{};
		if(direction.x != 0)
		{
			movement.first = static_cast<float>(direction.x * speed.value) * deltaTime;
			if(distanceTravelled.horizontal < EnemySettings::enemiesMaxHorizontalDistance &&
				distanceTravelled.horizontal + abs(movement.first) > EnemySettings::enemiesMaxHorizontalDistance)
			{
				movement.first = (EnemySettings::enemiesMaxHorizontalDistance - distanceTravelled.horizontal) * utils::Sign(direction.x);
				direction.x = 0;
				direction.y = 1;
			}
		}
		else if (direction.y != 0)
		{
			distanceTravelled.horizontal = 0;
			movement.second = static_cast<float>(direction.y * EnemySettings::enemyHeight);
			if(distanceTravelled.vertical < EnemySettings::enemiesMaxVerticalDistance &&
				distanceTravelled.vertical + abs(movement.second) > EnemySettings::enemiesMaxVerticalDistance)
			{
				SystemManager::STOP_SYSTEMS_EXECUTION = true;
				return;
			}
			direction.x = GetNewHorizontalDirection(position, startingPosX);
			direction.y = 0;
		}
		position.x += movement.first;
		position.y += movement.second;
		distanceTravelled.horizontal += abs(movement.first);
		distanceTravelled.vertical += abs(movement.second);
	}
}

int EnemyMovementSystem::GetNewHorizontalDirection(Position2D position, StartingPositionX startingPosX) const
{
	float endPos = startingPosX.value + EnemySettings::enemiesMaxHorizontalDistance;

	float distanceToLeftStartingPos = abs(position.x - startingPosX.value);
	float distanceToRightEndPos = abs(position.x - endPos);

	return utils::Sign(distanceToRightEndPos - distanceToLeftStartingPos);
}
