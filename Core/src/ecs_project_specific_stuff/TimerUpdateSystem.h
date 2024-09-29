#pragma once
#ifndef TIMERUPDATESYSTEM_H
#define TIMERUPDATESYSTEM_H

#include "../ecs_core/systems/SpecializedSystems.h"
#include "../ecs_core/EcsManager.h"

class TimerUpdateSystem : public LogicSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};
#endif // !TIMERUPDATESYSTEM_H

