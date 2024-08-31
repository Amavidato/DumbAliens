#include "MovementSystem.h"

#include "Components.h"
#include "../ecs_core/EcsManager.h"
void MovementSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Position2D, Speed, Direction2D, PlayerTag>();
}

void MovementSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for (auto entity : entities)
	{
		auto& position = ecsManager->GetComponent<Position2D>(entity);
		auto& speed = ecsManager->GetComponent<Speed>(entity);
		auto& direction = ecsManager->GetComponent<Direction2D>(entity);
		position.x += static_cast<float>(speed.value) * deltaTime * direction.x;
		position.y += static_cast<float>(speed.value) * deltaTime * direction.y;
	}
}
