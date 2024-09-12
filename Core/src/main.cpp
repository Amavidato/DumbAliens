#include "Game.h"
#include "settings/GameSettings.h"
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <format>

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

	Uint32 lastFrameTime {SDL_GetTicks()};
    while(Game::IS_RUNNING)
    {
        Uint32 frameStartTime = SDL_GetTicks();
        Uint32 frameDeltaTime = SDL_GetTicks() - lastFrameTime;
    	lastFrameTime = frameStartTime;
        game->Update(static_cast<float>(frameDeltaTime)/1000);
    }
    game->Clean();
    return 0;
}
