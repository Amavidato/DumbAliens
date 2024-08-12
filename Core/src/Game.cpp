#include "Game.h"

#include <format>
#include <iostream>

#include "SDL_image.h"

SDL_Texture *playerTexture;
SDL_Rect srcRect, destRect;
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
            SDL_SetRenderDrawColor(mpRenderer, 255,255,0,255);
            std::cout<<"Renderer Created!"<<std::endl;
        }
        mIsRunning = true;
    }
    SDL_Surface *tmpSurface = IMG_Load("assets/finn.png");
    playerTexture = SDL_CreateTextureFromSurface(mpRenderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
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
    destRect.h = 128;
    destRect.w = 64;
    destRect.x = mUpdatesCounter;
    std::cout << std::format("Frame number: {}",mUpdatesCounter)<<std::endl;
}

void Game::render()
{
    //First clear the renderer
    SDL_RenderClear(mpRenderer);
    //Than add stuff to the renderer
    SDL_RenderCopy(
        mpRenderer,
        playerTexture,
        NULL,
        &destRect);
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