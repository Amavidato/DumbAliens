#include "BulletMovementSystem.h"

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../settings/PlayerSettings.h"

void BulletMovementSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<BulletTag, Position2D, Direction2D>();
}

void BulletMovementSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for (auto bullet : entities)
	{
		auto& position = ecsManager->GetComponent<Position2D>(bullet);
		auto direction = ecsManager->GetComponent<Direction2D>(bullet);
		position.x += static_cast<float>(direction.x * PlayerSettings::BulletSettings::speed) * deltaTime;
		position.y += static_cast<float>(direction.y * PlayerSettings::BulletSettings::speed) * deltaTime;
	}
}
