#include <format>

#include "Game.h"
#include <iostream>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>

#include "settings/GameSettings.h"

Game *game = nullptr;

int main(int argc, char* argv[])
{
    game = new Game();
    game->Init(
        "This is my GameEngine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GameSettings::windowWidth,
        GameSettings::windowHeight,
        false);

	// TODO IMPLEMENT FIXED TIMESTEP UPDATES AND REFACTOR WHOLE GAME LOOP
    //const int targetFPS = 60;
    //const int targetDeltaTime = 1000/targetFPS;
	Uint32 lastFrameTime {SDL_GetTicks()};
    while(Game::IS_RUNNING)
    {
        Uint32 frameStartTime = SDL_GetTicks();
        Uint32 frameDeltaTime = SDL_GetTicks() - lastFrameTime;
    	lastFrameTime = frameStartTime;
        game->Update(static_cast<float>(frameDeltaTime)/1000);
    	
        // TODO CROPPING FPS...IMPLEMENT THIS AND REFACTOR WHOLE GAME LOOP
        /*
        if(targetDeltaTime > frameDeltaTime)
        {
            SDL_Delay(targetDeltaTime - frameDeltaTime);
        	std::cout << std::format("fdt: {}, tdt: {}, CROPPED: {}", frameDeltaTime, targetDeltaTime, targetDeltaTime - frameDeltaTime)<<std::endl;
        }
        */
    }
    game->Clean();
    return 0;
}
