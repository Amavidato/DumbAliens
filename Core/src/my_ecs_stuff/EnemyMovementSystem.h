#pragma once
#ifndef ENEMYMOVEMENTSYSTEM_H
#define ENEMYMOVEMENTSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class EnemyMovementSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // ENEMYMOVEMENTSYSTEM_H