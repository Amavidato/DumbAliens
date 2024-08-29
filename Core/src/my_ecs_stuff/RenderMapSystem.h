#pragma once
#ifndef RENDERMAPSYSTEM_H
#define RENDERMAPSYSTEM_H
#include "../ecs_core/systems/SpecializedSystems.h"
#include "../ecs_core/systems/System.h"

class RenderMapSystem : public RenderingSystem
{
public:
	~RenderMapSystem() = default;
	void OnCreate() override;
	void OnUpdate(float deltaTime, EcsManager* ecsManager) override;
};

#endif // RENDERMAPSYSTEM_H