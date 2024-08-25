#include "EntityManager.h"
#include <cassert>

EntityManager::EntityManager()
{
	for(Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		availableEntities_.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(livingEntityCount_ < MAX_ENTITIES && "Cannot create a new entity. Reached the limit of entities.");

	// Retrieve the next available id from the available queue
	Entity id = availableEntities_.front();
	availableEntities_.pop();
	++livingEntityCount_;
	return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	assert(livingEntityCount_ > 0 && "Cannot destroy the entity. There are no living entities.\n");

	// Invalidate the destroyed entity's signature
	signatures_[entity].reset();

	// Put the destroyed entity back into the available entities queue
	// TODO: WHAT IF THERE ARE NO CREATED ENTITIES
	// AND THE ENTITY WE ARE PUSHING IS ALREADY
	// INSIDE THE QUEUE?
	availableEntities_.push(entity);
	--livingEntityCount_;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	signatures_[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	return signatures_[entity];
}