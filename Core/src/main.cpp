#include "Game.h"

Game *game = nullptr;

int main(int argc, char* argv[])
{
    const int targetFPS = 60;
    const int targetDeltaTime = 1000/targetFPS;

    Uint32 frameStart;
    int frameDeltaTime;
    game = new Game();
    game->init(
        "This is my GameEngine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        false);
    
    while(game->isRunning())
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameDeltaTime = SDL_GetTicks() - frameStart;

        if(targetDeltaTime > frameDeltaTime)
        {
            SDL_Delay(targetDeltaTime - frameDeltaTime);   
        }
    }
    game->clean();
    return 0;
}
