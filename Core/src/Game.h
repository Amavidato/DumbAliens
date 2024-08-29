#ifndef GAME_H
#define GAME_H

#include <SDL_events.h>
#include <SDL_render.h>

#include "ecs_core/EcsManager.h"

class Game
{
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void update(float deltaTime);
    void clean();

	static std::unique_ptr<SDL_Renderer, decltype((SDL_DestroyRenderer))> renderer;
	static std::unique_ptr<SDL_Window, decltype((SDL_DestroyWindow))> window;
	static bool IS_RUNNING;
	static SDL_Event event;

private:
    int mUpdatesCounter;
    std::unique_ptr<EcsManager> pEcsManager_;
};
#endif