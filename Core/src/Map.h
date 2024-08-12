#pragma once
#ifndef MAP_H
#define MAP_H
#include <SDL_rect.h>
#include <SDL_render.h>

class Map
{
public:
    Map();
    ~Map();
    void LoadMap(int [20][25]);
    void DrawMap();
private:
    SDL_Rect mSrcRect, mDestRect;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;
    int mMap[20][25];
};

#endif // MAP_H