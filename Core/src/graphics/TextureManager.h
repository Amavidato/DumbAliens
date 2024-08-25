#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SDL_render.h>

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char* fileFullPath);
        static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);   
};

#endif