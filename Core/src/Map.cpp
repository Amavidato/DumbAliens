#include "Map.h"
#include "TextureManager.h"

int lvl1 [20][25] ={
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
};

Map::Map()
{
    dirt = TextureManager::LoadTexture("assets/map/dirt.png");
    grass = TextureManager::LoadTexture("assets/map/grass.png");
    water = TextureManager::LoadTexture("assets/map/water.png");

    LoadMap(lvl1);
}

void Map::LoadMap(int arr[20][25])
{
    for(int row = 0; row < 20; row++ )
    {
        for (int column = 0; column < 25; column++)
        {
            mMap[row][column] = arr[row][column];
        }
    }
    mSrcRect.x = mSrcRect.y = 0;
    mSrcRect.h = mDestRect.h = 32;
    mSrcRect.w = mDestRect.w = 32;
    mDestRect.x = mDestRect.y = 0;
}

void Map::DrawMap()
{
    int type = 0;
    for(int row = 0; row < 20; row++ )
    {
        for (int column = 0; column < 25; column++)
        {
            type = mMap[row][column];
            mDestRect.x = column * 32;
            mDestRect.y = row * 32;
            switch (type)
            {
                case 0 :
                    TextureManager::Draw(water, mSrcRect, mDestRect);
                    break;
                case 1 :
                    TextureManager::Draw(grass, mSrcRect, mDestRect);
                    break;
                case 2 :
                    TextureManager::Draw(dirt, mSrcRect, mDestRect);
                    break;
                default:
                    break;
            }
        }
    }
}

