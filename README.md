
# Dumb Aliens: a simple ECS project

I made this very tiny game just as an excuse to implement a simplified version of the architectural pattern known as **ECS (Enity-Component-System)** in **C++**.

## Project objectives
* Create a simple ECS from the ground up to better understand its inner working;
* Refreshing my knowledge of C++;


## Usage/Examples
This API is intended to be used mainly through its [EntityManager](https://github.com/Amavidato/DumbAliens/blob/master/Core/src/ecs_core/EcsManager.h) class.

#### Create an Entity:
```cpp
#include "ecs_core/EcsManager.h"
...
Entity entity = pEcsManager->CreateEntity();
...
```

#### Define a Component:
A component must be a class/struct that respect this constraints:
* **inherit** (publicly) from [AComponent](https://github.com/Amavidato/DumbAliens/blob/master/Core/src/ecs_core/components/Component.h);
* be a **POD** type: i.e. trivial and has standard layout (more on "*trivial and standard-layout types*" [here](https://en.cppreference.com/w/cpp/language/classes));
```cpp
#include "ecs_core/components/Component.h"

struct IsAliveTag : AComponent {};

struct Position2D : AComponent
{
	float x, y;
};
```
#### Add a Component to an Entity
```cpp
#include "ecs_core/components/Component.h"
#include "ecs_core/EcsManager.h"
...
pEcsManager->AddComponent(playerEntity, Position2D {.x = 20, .y = 20 });
pEcsManager->AddComponent<IsAliveTag>(entity);
...
```

#### Create a Signature
A Signature can be created by using the EcsManager's static method CreateSignature and chaining the various component types
```cpp
#include "ecs_core/EcsManager.h"
...
Signature signature = EcsManager::CreateSignature<Position2D, Speed, Direction2D, PlayerTag>();
...
```

#### Define a System
In this ECS implementation a new system must (publicly) inherit from one of the following specialized systems (you can find them [here](https://github.com/Amavidato/DumbAliens/blob/master/Core/src/ecs_core/systems/SpecializedSystems.h)):
* **InitializationSystem**: used to initialize enitites;
* **LogicSystem**: used to implement gameloop logic;
* **RenderingSystem**: used in rendering phase;
and it must override the public methods:
* **OnCreate**: executed once when the system is created. It is a good point to specify the "Signature" of the system (i.e. the set of components that an entity must have to be affected by this system).
* **OnUpdate**: executed once per frame. Logic goes here and will affect all entities (accessible via the  **entitites** field) having all the components specified in the system's signature
```cpp
//MovementSystem.h
#pragma once
#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "ecs_core/systems/SpecializedSystems.h"
#include "ecs_core/systems/System.h"

class MovementSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};
```
```cpp
//MovementSystem.cpp
#include "MovementSystem.h"
#include "ecs_core/EcsManager.h"

void MovementSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<Position2D, Speed, Direction2D, PlayerTag>();
}

void MovementSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	for (auto entity : entities)
	{
		auto& position = ecsManager->GetComponent<Position2D>(entity);
		auto& speed = ecsManager->GetComponent<Speed>(entity);
		auto& direction = ecsManager->GetComponent<Direction2D>(entity);
		auto movementX = static_cast<float>(speed.value) * deltaTime * direction.x;
		position.x += movementX;
		position.y += static_cast<float>(speed.value) * deltaTime * direction.y;
	}
}
#endif // MOVEMENT_SYSTEM_H
```

#### Register a system
A system, in order to run, must be registered in the EcsManager.
  In this ECS implementation, the systems registered in the EcsManager will be executed in this order:

1. systems that inherit from **InitializationSystem**;
2. systems that inherit from **LogicSystem**;
3. systems that inherit from **RenderingSystem**;

and within each group, systems are executed in order of registration.
```cpp
#include "ecs_core/EcsManager.h"
#include "MovementSystem.h"
...
pEcsManager->RegisterSystem(std::make_shared<MovementSystem>());
...
```


## Implementation
The core of this ecs implementation can be found at [DumbAliens/Core/src/ecs_core](https://github.com/Amavidato/DumbAliens/tree/master/Core/src/ecs_core).

WORK IN PROGRESS...
