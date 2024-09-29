#include "TimerUpdateSystem.h"
#include "Components.h"
#include "../ecs_core/EcsManager.h"

void TimerUpdateSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Timer>();
}

void TimerUpdateSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for(auto entity : entities)
	{
		auto& timer = ecsManager->GetComponent<Timer>(entity);
		timer.elapsedTimeInSeconds += deltaTime;
	}
}
