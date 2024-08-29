#include "TextureManager.h"
#include "../Game.h"
#include <iostream>
#include <SDL_image.h>
#include <filesystem>

std::unordered_map<const char*, SDL_Texture*> TextureManager::texturesCache_ {};

SDL_Texture* TextureManager::LoadTexture(const char* fileFullPath)
{
    if(!texturesCache_.contains(fileFullPath))
    {
    	if(!std::filesystem::exists(fileFullPath))
    	{
    		std::cout << std::format("File does't exists at path:{}!",fileFullPath) << std::endl;
    		return nullptr;
    	}
	    SDL_Surface* tempSurface = IMG_Load(fileFullPath);
	    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer.get(), tempSurface);
	    SDL_FreeSurface(tempSurface);
    	texturesCache_.insert({fileFullPath,texture});
    }
    return texturesCache_[fileFullPath];
}

void TextureManager::Draw(SDL_Texture* texture, SDL_FRect dest)
{
	SDL_RenderCopyF(Game::renderer.get(), texture, NULL, &dest);
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_FRect dest)
{
    SDL_RenderCopyF(Game::renderer.get(), texture, &src, &dest);
}
