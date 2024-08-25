#include "TextureManager.h"

#include <iostream>
#include <SDL_image.h>
#include <filesystem>

#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileFullPath)
{
    if(!std::filesystem::exists(fileFullPath))
    {
        std::cout << std::format("File does't exists at path:{}!",fileFullPath) << std::endl;
        return nullptr;
    }
    
    SDL_Surface* tempSurface = IMG_Load(fileFullPath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mpRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::mpRenderer, texture, &src, &dest);
}

