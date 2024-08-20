#pragma once
#ifndef ECS
#define ECS

#include "ecsAliases.h"
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
	std::queue<Entity> mAvailableEntities{};
	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> mSignatures{};
	// Total living entities - used to keep limits on how many entities can exist
	uint32_t mLivingEntityCount{};
};
#endif