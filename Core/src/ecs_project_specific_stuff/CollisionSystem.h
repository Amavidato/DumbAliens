#pragma once
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class CollisionSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // COLLISIONSYSTEM_H
