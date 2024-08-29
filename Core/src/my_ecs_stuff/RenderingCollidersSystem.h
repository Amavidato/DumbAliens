#pragma once
#ifndef RENDERINGCOLLIDERSSYSTEM_H
#define RENDERINGCOLLIDERSSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"

class RenderingCollidersSystem : public RenderingSystem
{
public:
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // RENDERINGCOLLIDERSSYSTEM_H