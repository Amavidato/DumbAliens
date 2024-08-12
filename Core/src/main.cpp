#include "Game.h"

Game *game = nullptr;

int main(int argc, char* argv[])
{
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
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}
