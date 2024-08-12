#ifndef GAME_H
#define GAME_H

#include "SDL.h"

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
private:
    int mUpdatesCounter;
    bool mIsRunning;
    SDL_Window *mpWindow;
    SDL_Renderer *mpRenderer;
};
#endif