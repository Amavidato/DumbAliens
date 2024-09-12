#ifndef GAME_H
#define GAME_H

#include <SDL_events.h>
#include <SDL_render.h>
#include "ecs_core/EcsManager.h"

class Game
{
public:
    Game() = default;
    ~Game() = default;
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void Update(float deltaTime);
    void Clean();

	static std::unique_ptr<SDL_Renderer, decltype((SDL_DestroyRenderer))> renderer;
	static std::unique_ptr<SDL_Window, decltype((SDL_DestroyWindow))> window;
	static bool IS_RUNNING;
	static int SCORE;
	static SDL_Event event;
	
private:
    int mUpdatesCounter;
    std::unique_ptr<EcsManager> pEcsManager_;
	void InitWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void InitEcsSystems();
	void InitPlayer();
	void InitEnemies();
	void SetupScoreLabelForRender();
	//void InitMap();
};
#endif