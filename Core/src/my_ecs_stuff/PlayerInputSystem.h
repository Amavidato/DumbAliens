#pragma once
#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class PlayerInputSystem : public InitializationSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
private:
	void Shoot(EcsManager* ecsManager, Entity entity) const;
	bool CanShoot(EcsManager* ecsManager, Entity entity) const;
};

#endif // PLAYERINPUTSYSTEM_H