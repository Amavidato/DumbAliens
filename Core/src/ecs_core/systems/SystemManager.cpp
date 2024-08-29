#include "SystemManager.h"
#include "../../Game.h"

bool SystemManager::STOP_SYSTEMS_EXECUTION = false;

void SystemManager::UpdateSystems(float deltaTime, EcsManager* ecsManager)
{
	std::shared_ptr<ASystem> tempSystem;
	for (auto system : systemsSet_)
	{
		if(STOP_SYSTEMS_EXECUTION)
		{
			Game::IS_RUNNING = false;
			break;
		}
		system->OnUpdate(deltaTime, ecsManager);
	}
}
