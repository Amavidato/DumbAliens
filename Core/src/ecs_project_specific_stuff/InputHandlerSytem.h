#pragma once
#ifndef INPUTHANDLERSYTEM_H
#define INPUTHANDLERSYTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class InputHandlerSytem : public InitializationSystem
{
public:
	void OnCreate();
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // INPUTHANDLERSYTEM_H