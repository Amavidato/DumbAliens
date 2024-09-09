#include "Game.h"

#include <format>
#include <iostream>

#include "SDL_image.h"
#include "graphics/TextureManager.h"
#include "my_ecs_stuff/BulletMovementSystem.h"
#include "my_ecs_stuff/CollisionSystem.h"
#include "my_ecs_stuff/Components.h"
#include "my_ecs_stuff/EnemyMovementSystem.h"
#include "my_ecs_stuff/InputHandlerSytem.h"
#include "my_ecs_stuff/MovementSystem.h"
#include "my_ecs_stuff/PlayerInputSystem.h"
#include "my_ecs_stuff/RendererSystem.h"
#include "my_ecs_stuff/RenderingCollidersSystem.h"
#include "my_ecs_stuff/RenderMapSystem.h"
#include "my_ecs_stuff/BulletCollisionSystem.h"
#include "my_ecs_stuff/BulletAutodestructionSystem.h"
#include "my_ecs_stuff/TimerUpdateSystem.h"
#include "settings/EnemySettings.h"
#include "settings/GameSettings.h"
#include "settings/PlayerSettings.h"

std::unique_ptr<Entity> player;
std::unique_ptr<Entity> enemies[EnemySettings::NumEnemies()];
std::unique_ptr<Entity> map;
std::unique_ptr<SDL_Renderer, decltype((SDL_DestroyRenderer))> Game::renderer {nullptr,SDL_DestroyRenderer};
std::unique_ptr<SDL_Window, decltype((SDL_DestroyWindow))> Game::window {nullptr,SDL_DestroyWindow};
bool Game::IS_RUNNING = false;

SDL_Event Game::event;
	
Game::Game()
{
	
}

Game::~Game()
{
    
}

void Game::Init(
    const char* title,
    int xpos,
    int ypos,
    int width,
    int height,
    bool fullscreen)
{
	InitWindow(title,
			xpos,
			ypos,
			width,
			height,
			fullscreen);
	InitEcsSystems();
	InitPlayer();
	InitEnemies();
	//InitMap();
}

void Game::Update(float deltaTime)
{
	SDL_PollEvent(&event);
    mUpdatesCounter++;
	//First clear the renderer
	SDL_RenderClear(Game::renderer.get());
    pEcsManager_->UpdateSystems(deltaTime);
	//Finally repaint the renderer with the new stuff
	SDL_RenderPresent(Game::renderer.get());
	std::cout << std::format("Frame number: {}",mUpdatesCounter)<<std::endl;
}

void Game::Clean()
{
    SDL_DestroyWindow(window.get());
    SDL_DestroyRenderer(renderer.get());
    SDL_Quit();
    std::cout << "Game Cleaned!"<<std::endl;
}

void Game::InitWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	mUpdatesCounter = 0;
	if(fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
    
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout<<"Subsystem Initialising..."<<std::endl;
		window.reset(
			SDL_CreateWindow(
			title,
			xpos,
			ypos,
			width,
			height,
			flags)
		);
		if(window)
		{
			std::cout<<"Window Created!"<<std::endl;
		}
		renderer.reset(SDL_CreateRenderer(window.get(), -1, 0));
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer.get(), 0,0,0,255);
			std::cout<<"Renderer Created!"<<std::endl;
		}
		IS_RUNNING = true;
	}
}

void Game::InitEcsSystems()
{
	pEcsManager_ = std::make_unique<EcsManager>();
	pEcsManager_->RegisterSystem(std::make_shared<RenderMapSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<MovementSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<RendererSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<InputHandlerSytem>());
	pEcsManager_->RegisterSystem(std::make_shared<PlayerInputSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<TimerUpdateSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<BulletAutodestructionSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<CollisionSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<RenderingCollidersSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<EnemyMovementSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<BulletMovementSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<BulletCollisionSystem>());
}

void Game::InitPlayer()
{
	player = std::make_unique<Entity>(pEcsManager_->CreateEntity());
	pEcsManager_->AddComponent<PlayerTag>(*player);
	pEcsManager_->AddComponent(*player, Position2D{
		.x = 300 - PlayerSettings::playerWidth,
		.y = 600 - PlayerSettings::playerHeight
	});
	pEcsManager_->AddComponent(*player, Collider2D{
		.width = PlayerSettings::playerWidth,
		.height = PlayerSettings::playerHeight
	});
	pEcsManager_->AddComponent(*player, Speed{{},PlayerSettings::speed});
	pEcsManager_->AddComponent(*player, Direction2D{{},0,0});
	pEcsManager_->AddComponent(*player,
		RendererData{
			.texturePath = PlayerSettings::texturePath,
			.width = PlayerSettings::playerWidth,
			.height = PlayerSettings::playerHeight
		});
}

void Game::InitEnemies()
{
	for(int i = 0; i < EnemySettings::NumEnemies(); i++)
	{
		float startingPosX = static_cast<float>((i % EnemySettings::numOfEnemiesPerRow) * EnemySettings::enemyWidth + (i % EnemySettings::numOfEnemiesPerRow) * EnemySettings::enemyPadding);
		enemies[i] = std::make_unique<Entity>(pEcsManager_->CreateEntity());
		pEcsManager_->AddComponent(*enemies[i], Position2D{
			.x = startingPosX,
			.y = static_cast<float>((i / EnemySettings::numOfEnemiesPerRow) * EnemySettings::enemyHeight + (i / EnemySettings::numOfEnemiesPerRow) * EnemySettings::enemyPadding)
		});

		pEcsManager_->AddComponent(*enemies[i], StartingPositionX{
			.value = startingPosX
		});
		pEcsManager_->AddComponent(*enemies[i], Collider2D{
			.width = EnemySettings::enemyWidth,
			.height = EnemySettings::enemyHeight
		});
		pEcsManager_->AddComponent(*enemies[i], Speed{{},EnemySettings::speed});
		pEcsManager_->AddComponent(*enemies[i], RendererData{
			.texturePath = EnemySettings::texturePath,
			.width = EnemySettings::enemyWidth,
			.height = EnemySettings::enemyHeight
		});
		pEcsManager_->AddComponent(*enemies[i], Direction2D{{},1,0});
		pEcsManager_->AddComponent<EnemyTag>(*enemies[i]);
		pEcsManager_->AddComponent(*enemies[i], DistanceTravelled{
			.horizontal = 0,
			.vertical = 0
		});
	}
}

/*
void Game::InitMap()
{
	map = std::make_unique<Entity>(pEcsManager_->CreateEntity());

	pEcsManager_->AddComponent(*map,
		TerrainTiles{
			.terrainTilesIds = {
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,2,2,2,1,1,2,1,0,2,2,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				}
		});
	pEcsManager_->AddComponent(*map,
		TilesInfo{
			.mapIndexToTexturePath =
				{
				"assets/map/water.png",
				"assets/map/grass.png",
				"assets/map/dirt.png"
			},
			.tileWidth = 32,
			.tileHeight = 32
		});
}
*/


