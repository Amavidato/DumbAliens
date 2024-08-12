#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "Map.h"

class Game
{
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning();

    static SDL_Renderer* mpRenderer;

private:
    int mUpdatesCounter;
    bool mIsRunning;
    SDL_Window* mpWindow;
};
#endif