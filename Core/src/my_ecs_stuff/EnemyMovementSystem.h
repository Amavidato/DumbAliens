#pragma once
#ifndef ENEMYMOVEMENTSYSTEM_H
#define ENEMYMOVEMENTSYSTEM_H
#include "Components.h"
#include "../ecs_core/systems/SpecializedSystems.h"

class EnemyMovementSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;

private:
	int GetNewHorizontalDirection(Position2D position, StartingPositionX startingPosX) const;
};

#endif // ENEMYMOVEMENTSYSTEM_H