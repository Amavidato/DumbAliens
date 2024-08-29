#include "RendererSystem.h"

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../graphics/TextureManager.h"
#include "../Game.h"

void RendererSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Position2D, RendererData>();
}

void RendererSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	SDL_FRect rect;
	//Than add stuff to the renderer
	for (auto entity : entities)
	{
		auto& renderData = ecsManager->GetComponent<RendererData>(entity);
		auto& positionData = ecsManager->GetComponent<Position2D>(entity);
		auto texture = TextureManager::LoadTexture(renderData.texturePath);

		rect.h = renderData.height;
		rect.w = renderData.width;
		rect.x = positionData.x;
		rect.y = positionData.y;
		TextureManager::Draw(texture, rect);
	}
}