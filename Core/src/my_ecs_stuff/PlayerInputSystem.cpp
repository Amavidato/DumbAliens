#include "PlayerInputSystem.h"

#include <SDL_events.h>

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../Game.h"
#include "../settings/PlayerSettings.h"

void PlayerInputSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Direction2D, PlayerTag>();
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
			case SDLK_LEFT:
				direction.x = -1;
				break;
			case SDLK_RIGHT:
				direction.x = 1;
				break;
			case SDLK_SPACE:
			 	Shoot(ecsManager, entity);
			 	break;
			default:
				break;
			}
		}

		if(Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
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

void PlayerInputSystem::Shoot(EcsManager* ecsManager, Entity playerEntity)
{
	auto bullet = ecsManager->CreateEntity();
	ecsManager->AddComponent<BulletTag>(bullet);
	auto position = ecsManager->GetComponent<Position2D>(playerEntity);
	position.x += PlayerSettings::playerWidth / 2;
	ecsManager->AddComponent<Position2D>(bullet, position);
	ecsManager->AddComponent<Direction2D>(bullet, Direction2D{.x = 0,.y = -1});
	ecsManager->AddComponent<RendererData>(bullet, RendererData{
		.texturePath = PlayerSettings::BulletSettings::texturePath,
		.width = PlayerSettings::BulletSettings::width,
		.height = PlayerSettings::BulletSettings::height
	});
	ecsManager->AddComponent<Collider2D>(bullet, Collider2D{
		.width = PlayerSettings::BulletSettings::width,
		.height = PlayerSettings::BulletSettings::height
	});
	ecsManager->AddComponent(bullet, Timer{
		.durationInSeconds = PlayerSettings::BulletSettings::lifetimeInSeconds,
		.elapsedTimeInSeconds = 0
	});
}
