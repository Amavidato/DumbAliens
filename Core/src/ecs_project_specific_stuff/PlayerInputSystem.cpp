﻿#include "PlayerInputSystem.h"

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

void PlayerInputSystem::Shoot(EcsManager* ecsManager, Entity playerEntity) const
{
	if (!CanShoot(ecsManager, playerEntity))
		return;
	if (ecsManager->HasComponent<Timer>(playerEntity))
	{
		auto& timer = ecsManager->GetComponent<Timer>(playerEntity);
		timer.elapsedTimeInSeconds = 0;
	}
	else
	{
		ecsManager->AddComponent(playerEntity, Timer{
			.durationInSeconds = PlayerSettings::secondsBetweenShoots,
			.elapsedTimeInSeconds = 0
			});
	}

	auto bullet = ecsManager->CreateEntity();
	ecsManager->AddComponent<BulletTag>(bullet);
	auto position = ecsManager->GetComponent<Position2D>(playerEntity);
	position.x += PlayerSettings::playerWidth / 2;
	position.y -= PlayerSettings::BulletSettings::height;
	ecsManager->AddComponent(bullet, position);
	ecsManager->AddComponent(bullet, Direction2D{.x = 0,.y = -1});
	ecsManager->AddComponent(bullet, RendererData{
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

bool PlayerInputSystem::CanShoot(EcsManager* ecsManager, Entity entity) const
{
	if (ecsManager->HasComponent<Timer>(entity)) 
	{
		auto timer = ecsManager->GetComponent<Timer>(entity);
		return timer.elapsedTimeInSeconds > timer.durationInSeconds;
	}
	return true;
}

