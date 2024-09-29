#pragma once
#ifndef BULLETCOLLISIONSYSTEM_H
#define BULLETCOLLISIONSYSTEM_H
#include "../../ecs_core/systems/SpecializedSystems.h"

class BulletCollisionSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // BULLETCOLLISIONSYSTEM_H