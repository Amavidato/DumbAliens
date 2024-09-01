#include "RenderingCollidersSystem.h"

#include <SDL_render.h>

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../Game.h"

void RenderingCollidersSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Collider2D, Position2D>();
}

void RenderingCollidersSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for (auto entity : entities)
	{
		auto& position = ecsManager->GetComponent<Position2D>(entity);
		auto& collider = ecsManager->GetComponent<Collider2D>(entity);
		SDL_FRect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.w = collider.width;
		rect.h = collider.height;
		SDL_SetRenderDrawColor(Game::renderer.get(), 255,0,0,255);
		SDL_RenderDrawRectF(Game::renderer.get(), &rect);
	}
	SDL_SetRenderDrawColor(Game::renderer.get(), 0,0,0,255);
}
