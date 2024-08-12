#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SDL_render.h>

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char* fileFullPath, SDL_Renderer* renderer);
    
};

#endif