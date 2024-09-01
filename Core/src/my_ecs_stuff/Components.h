#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../ecs_core/components/Component.h"

struct Position2D : AComponent
{
	float x, y;
};

struct Speed : AComponent
{
	int value;
};

struct RendererData : AComponent
{
	const char* texturePath;
	int width, height;
};

struct TerrainTiles : AComponent
{
	int terrainTilesIds[20][25];
};

struct TilesInfo : AComponent
{
	const char* mapIndexToTexturePath[3];
	int tileWidth, tileHeight;
};

struct Direction2D : AComponent
{
	int x, y;
};

struct Collider2D : AComponent
{
	int width, height;
};

struct PlayerTag : AComponent{};
struct EnemyTag : AComponent{};
struct BulletTag : AComponent{};

#endif // COMPONENTS_H