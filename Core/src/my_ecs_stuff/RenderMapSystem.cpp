#include "RenderMapSystem.h"

#include <SDL_rect.h>

#include "Components.h"
#include "../ecs_core/EcsManager.h"
#include "../graphics/TextureManager.h"

void RenderMapSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<TerrainTiles, TilesInfo>();
}

void RenderMapSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	SDL_FRect rect;
	//Than add stuff to the renderer
	for (auto entity : entities)
	{
		
		auto& terrainTiles = ecsManager->GetComponent<TerrainTiles>(entity);
		auto& tilesInfo = ecsManager->GetComponent<TilesInfo>(entity);
		rect.h = tilesInfo.tileHeight;
		rect.w = tilesInfo.tileWidth;

		int numRows = std::end(terrainTiles.terrainTilesIds) - std::begin(terrainTiles.terrainTilesIds);
		int numColumns = std::end(terrainTiles.terrainTilesIds[0]) - std::begin(terrainTiles.terrainTilesIds[0]);
		for(int row = 0; row < numRows; row++ )
		{
			for (int column = 0; column < numColumns; column++)
			{
				int type = terrainTiles.terrainTilesIds[row][column];
				rect.x = column * tilesInfo.tileWidth;
				rect.y = row * tilesInfo.tileHeight;
				SDL_Texture* texture = TextureManager::LoadTexture(tilesInfo.mapIndexToTexturePath[type]);
				TextureManager::Draw(texture, rect);
			}
		}
	}
}
