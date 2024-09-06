#pragma once
#ifndef ECSCOMMANDBUFFER_H
#define ECSCOMMANDBUFFER_H

#include "../EcsManager.h"
#include "EcsCommands.h"
#include <set>


class EcsCommandBuffer
{
public:
	EcsCommandBuffer(std::shared_ptr<EcsManager> ecsManager);
	~EcsCommandBuffer() = default;
	
	template <IsAComponentStruct T>
	void AddComponent(Entity entity, T component)
	{
		commands_.insert(AddComponentCommand(entity,component));
	}

	void DestroyEntity(Entity entity)
	{
		EcsCommand* ec = new DestroyEntityCommand(entity);
		commands_.insert(ec);
	}
	void Execute();
private:
	std::set<EcsCommand*> commands_;
	std::shared_ptr<EcsManager> ecsManager_;
};


#endif // ECSCOMMANDBUFFER_H