#include <iostream>

#include "Game.h"
#include "ECS/componentArray.h"
#include "ECS/componentManager.h"
#include "ECS/entityManager.h"

Game *game = nullptr;

class Rigidbody
{
public:
	double Value;
};

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
	ComponentArray<Rigidbody> array {};

	std::unordered_map<Entity, size_t> map;
	
	EntityManager* em = new EntityManager();
	auto ent = em->CreateEntity();
	if(map.find(ent) == map.end())
		std::cout<<"NOT CONTAINS"<<std::endl;
	ComponentManager* manager = new ComponentManager();
	manager->RegisterComponent<Rigidbody>();
	manager->AddComponent(ent, Rigidbody{9.9});
	em->DestroyEntity(ent);
	/*
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
    */
    game->clean();
    return 0;
}
