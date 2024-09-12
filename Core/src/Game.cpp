#include "Game.h"
#include "SDL_ttf.h"

#include "graphics/TextureManager.h"
#include "my_ecs_stuff/BulletSystems/BulletMovementSystem.h"
#include "my_ecs_stuff/CollisionSystem.h"
#include "my_ecs_stuff/Components.h"
#include "my_ecs_stuff/EnemyMovementSystem.h"
#include "my_ecs_stuff/InputHandlerSytem.h"
#include "my_ecs_stuff/MovementSystem.h"
#include "my_ecs_stuff/PlayerInputSystem.h"
#include "my_ecs_stuff/RendererSystem.h"
#include "my_ecs_stuff/RenderingCollidersSystem.h"
#include "my_ecs_stuff/BulletSystems/BulletCollisionSystem.h"
#include "my_ecs_stuff/BulletSystems/BulletAutodestructionSystem.h"
#include "my_ecs_stuff/TimerUpdateSystem.h"
#include "settings/EnemySettings.h"
#include "settings/GameSettings.h"
#include "settings/PlayerSettings.h"

#include "SDL_image.h"
#include <string>
#include <format>
#include <iostream>

std::unique_ptr<Entity> player;
std::unique_ptr<Entity> enemies[EnemySettings::NumEnemies()];
std::unique_ptr<Entity> map;
std::unique_ptr<SDL_Renderer, decltype((SDL_DestroyRenderer))> Game::renderer {nullptr,SDL_DestroyRenderer};
std::unique_ptr<SDL_Window, decltype((SDL_DestroyWindow))> Game::window {nullptr,SDL_DestroyWindow};
bool Game::IS_RUNNING = false;
int Game::SCORE{0};
SDL_Event Game::event;

void Game::Init(
    const char* title,
    int xpos,
    int ypos,
    int width,
    int height,
    bool fullscreen)
{
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	} 
	InitWindow(title,
			xpos,
			ypos,
			width,
			height,
			fullscreen);
	InitEcsSystems();
	InitPlayer();
	InitEnemies();
}

void Game::Update(float deltaTime)
{
	SDL_PollEvent(&event);
    mUpdatesCounter++;
	//First clear the renderer
	SDL_RenderClear(Game::renderer.get());
	//Then fill with things to draw
    pEcsManager_->UpdateSystems(deltaTime);
	SetupScoreLabelForRender();
	
	//Finally repaint the renderer with the new stuff
	SDL_RenderPresent(Game::renderer.get());
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
	pEcsManager_->RegisterSystem(std::make_shared<MovementSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<RendererSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<InputHandlerSytem>());
	pEcsManager_->RegisterSystem(std::make_shared<PlayerInputSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<TimerUpdateSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<BulletAutodestructionSystem>());
	pEcsManager_->RegisterSystem(std::make_shared<CollisionSystem>());
	//pEcsManager_->RegisterSystem(std::make_shared<RenderingCollidersSystem>());
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

void Game::SetupScoreLabelForRender()
{
	TTF_Font* Font = TTF_OpenFont("assets/CascadiaCode.ttf", 24);
	SDL_Color FontColor{ 255, 255, 255 };

	std::string scoreLabel{ "SCORE: " };
	scoreLabel.append(std::to_string(Game::SCORE));
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, scoreLabel.c_str(), FontColor);

	if (surfaceMessage == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer.get(), surfaceMessage);
		if (Message == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_Rect Message_rect{
				.x = 0,
				.y = 0,
				.w = 0,
				.h = 0
			};
			TTF_SizeText(Font, scoreLabel.c_str(), &Message_rect.w, &Message_rect.h);
			SDL_RenderCopy(Game::renderer.get(), Message, NULL, &Message_rect);
		}
	}
}