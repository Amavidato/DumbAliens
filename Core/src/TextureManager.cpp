#include "TextureManager.h"

#include <iostream>
#include <SDL_image.h>
#include <filesystem>

SDL_Texture* TextureManager::LoadTexture(const char* fileFullPath, SDL_Renderer* renderer)
{
    if(!std::filesystem::exists(fileFullPath))
    {
        std::cout << std::format("File does't exists at path:{}!",fileFullPath) << std::endl;
        return nullptr;
    }
    
    SDL_Surface* tempSurface = IMG_Load(fileFullPath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}
