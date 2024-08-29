#pragma once
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class CollisionSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
private:
	bool IsThereACollision(Entity entity1, Entity entity2, EcsManager* ecsManager);
};

#endif // COLLISIONSYSTEM_H
