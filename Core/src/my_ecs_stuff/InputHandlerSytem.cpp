#include "InputHandlerSytem.h"
#include "../ecs_core/systems/SystemManager.h"
#include "../Game.h"
#include <SDL_events.h>

void InputHandlerSytem::OnCreate()
{
}

void InputHandlerSytem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	switch (Game::event.type)
	{
	case SDL_QUIT:
		SystemManager::STOP_SYSTEMS_EXECUTION = true;
		break;
	default:
		break;
	}
	
	if(Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			SystemManager::STOP_SYSTEMS_EXECUTION = true;
			break;
		default:
			break;
		}
	}
}
