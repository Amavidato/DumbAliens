#include "Game.h"

#include <format>
#include <iostream>

#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
GameObject* enemy;

SDL_Renderer* Game::mpRenderer = nullptr;
Map* map;

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::init(
    const char* title,
    int xpos,
    int ypos,
    int width,
    int height,
    bool fullscreen)
{
    int flags = 0;
    mUpdatesCounter = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"Subsystem Initialising..."<<std::endl;
        mpWindow = SDL_CreateWindow(
            title,
            xpos,
            ypos,
            width,
            height,
            flags);
        if(mpWindow)
        {
            std::cout<<"Window Created!"<<std::endl;
        }
        mpRenderer = SDL_CreateRenderer(mpWindow, -1, 0);
        if(mpRenderer)
        {
            SDL_SetRenderDrawColor(mpRenderer, 255,255,255,255);
            std::cout<<"Renderer Created!"<<std::endl;
        }
        mIsRunning = true;
    }

    player = new GameObject("assets/finn.png",0,0);
    enemy = new GameObject("assets/enemy.png",70,70);

    map = new Map();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    mUpdatesCounter++;
    player->Update();
    enemy->Update();
    std::cout << std::format("Frame number: {}",mUpdatesCounter)<<std::endl;
}

void Game::render()
{
    //First clear the renderer
    SDL_RenderClear(mpRenderer);
    //Than add stuff to the renderer
    map->DrawMap();
    player->Render();
    enemy->Render();
    //Finally repaint the renderer with the new stuff
    SDL_RenderPresent(mpRenderer);
    
}

void Game::clean()
{
    SDL_DestroyWindow(mpWindow);
    SDL_DestroyRenderer(mpRenderer);
    SDL_Quit();
    std::cout << "Game Cleaned!"<<std::endl;
}

bool Game::isRunning()
{
    return mIsRunning;    
}