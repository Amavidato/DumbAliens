#include "MovementSystem.h"

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../settings/PlayerSettings.h"
#include "../settings/GameSettings.h"

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
		auto movementX = static_cast<float>(speed.value) * deltaTime * direction.x;
		if (IsBlockedByBorder(position.x, movementX))
			return;
		position.x += movementX;
		position.y += static_cast<float>(speed.value) * deltaTime * direction.y;
	}
}

bool MovementSystem::IsBlockedByBorder(const float positionX, const float movementX) const 
{
	auto resultingPositionX = positionX + movementX;
	if (resultingPositionX < 0 || resultingPositionX + PlayerSettings::playerWidth > GameSettings::windowHeight)
		return true;
	return false;

}
