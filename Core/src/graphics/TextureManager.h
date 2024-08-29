#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SDL_render.h>
#include <unordered_map>

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char* fileFullPath);
        static void Draw(SDL_Texture* texture, SDL_FRect dest);
        static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_FRect dest);
	private:
		static std::unordered_map<const char*, SDL_Texture*> texturesCache_;
};

#endif