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
	// Queue that stores unused entity IDs
	std::queue<Entity> availableEntities_{};
	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> signatures_{};
	// Total living entities - used to keep limits on how many entities can exist
	uint32_t livingEntityCount_ {};
};
#endif