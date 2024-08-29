#pragma once
#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class PlayerInputSystem : public InitializationSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // PLAYERINPUTSYSTEM_H