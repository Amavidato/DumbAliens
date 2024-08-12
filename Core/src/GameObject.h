#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"

class GameObject
{
public:
    GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
    ~GameObject();
    void Update();
    void Render();
    
private:
    int xpos, ypos;
    SDL_Texture* mObjectTexture;
    SDL_Rect mSrcRect, mDestRect;
    SDL_Renderer* mRenderer;
};

#endif // GAMEOBJECT_H