#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <iostream>

struct Position2D
{
	float x, y;
};

struct Speed
{
	int value;
};

struct RendererData
{
	const char* texturePath;
	int width, height;
};

struct TerrainTiles
{
	int terrainTilesIds[20][25];
};

struct TilesInfo
{
	const char* mapIndexToTexturePath[3];
	int tileWidth, tileHeight;
};

struct Direction2D
{
	int x,y;
};

struct Collider2D
{
	int width, height;
};

struct DistanceTravelled
{
	float horizontal, vertical;
};

struct StartingPositionX
{
	float value;
};
struct PlayerTag
{};
struct EnemyTag
{};
struct BulletTag
{};

struct Timer 
{
	float durationInSeconds;
	float elapsedTimeInSeconds;
};

#endif // COMPONENTS_H