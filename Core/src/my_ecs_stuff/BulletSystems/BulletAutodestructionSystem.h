#pragma once
#ifndef BULLETAUTODESTRUCTION_H
#define BULLETAUTODESTRUCTION_H

#include "../../ecs_core/systems/SpecializedSystems.h"

class BulletAutodestructionSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;

};
#endif // !BULLETAUTODESTRUCTION_H

