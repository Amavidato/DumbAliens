#pragma once
#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"
#include "../ecs_core/systems/System.h"

class MovementSystem : public LogicSystem
{
public:
	MovementSystem() = default;
	~MovementSystem() override = default;
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // MOVEMENTSYSTEM_H