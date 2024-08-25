#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"

class GameObject
{
public:
    GameObject(const char* textureSheet);
    ~GameObject();
private:
	Entity* entity;
};

#endif // GAMEOBJECT_H