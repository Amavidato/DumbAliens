#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"

class GameObject
{
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();
    void Update();
    void Render();
    
private:
    int xpos, ypos;
    SDL_Texture* mObjectTexture;
    SDL_Rect mSrcRect, mDestRect;
};

#endif // GAMEOBJECT_H