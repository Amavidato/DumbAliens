#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "../EcsAliases.h"
#include <queue>
#include <array>

class EntityManager
{
public:
	EntityManager();
	~EntityManager() = default;
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity);

private:
	// Unused entity IDs
	std::queue<Entity> availableEntities_{};
	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> signatures_{};
	// Total living entities
	int livingEntityCount_ {};
};
#endif