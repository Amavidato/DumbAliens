#pragma once
#ifndef RENDERERSYSTEM_H
#define RENDERERSYSTEM_H

#include "../ecs_core/systems/SpecializedSystems.h"
#include "../ecs_core/systems/System.h"

class RendererSystem : public RenderingSystem
{
public:
	~RendererSystem() override = default;
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // RENDERERSYSTEM_H