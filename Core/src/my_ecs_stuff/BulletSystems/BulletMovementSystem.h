#pragma once
#ifndef BULLETMOVEMENTSYSTEM_H
#define BULLETMOVEMENTSYSTEM_H
#include "../../ecs_core/systems/SpecializedSystems.h"

class BulletMovementSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // BULLETMOVEMENTSYSTEM_H