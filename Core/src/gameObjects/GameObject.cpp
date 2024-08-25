#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    mObjectTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
}

GameObject::~GameObject()
{
    
}

void GameObject::Update()
{
    xpos++;
    ypos++;
    mSrcRect.h = 230;
    mSrcRect.w = 150;
    mSrcRect.x = 0;
    mSrcRect.y = 0;

    mDestRect.x = xpos;
    mDestRect.y = ypos;
    mDestRect.w = mSrcRect.w / 2;
    mDestRect.h = mSrcRect.h / 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::mpRenderer, mObjectTexture, &mSrcRect,&mDestRect);
}



