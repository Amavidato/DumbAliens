#include "PlayerInputSystem.h"

#include <SDL_events.h>

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../Game.h"

void PlayerInputSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Direction2D>();
}

void PlayerInputSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for (auto entity: entities)
	{
		auto& direction = ecsManager->GetComponent<Direction2D>(entity);
		
		if(Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				direction.y = -1;
				break;
			case SDLK_DOWN:
				direction.y = 1;
				break;
			case SDLK_LEFT:
				direction.x = -1;
				break;
			case SDLK_RIGHT:
				direction.x = 1;
				break;
			default:
				break;
			}
		}

		if(Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				direction.y = 0;
				break;
			case SDLK_DOWN:
				direction.y = 0;
				break;
			case SDLK_LEFT:
				direction.x = 0;
				break;
			case SDLK_RIGHT:
				direction.x = 0;
				break;
			default:
				break;
			}
		}
	}
}
