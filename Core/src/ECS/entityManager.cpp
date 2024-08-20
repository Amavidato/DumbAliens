#include "entityManager.h"
#include <cassert>

EntityManager::EntityManager()
{
	for(Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		mAvailableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(mLivingEntityCount < MAX_ENTITIES && "Cannot create a new entity. Reached the limit of entities.");

	// Retrieve the next available id from the available queue
	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	++mLivingEntityCount;
	return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	assert(mLivingEntityCount > 0 && "Cannot destroy the entity. There are no living entities.\n");

	// Invalidate the destroyed entity's signature
	mSignatures[entity].reset();

	// Put the destroyed entity back into the available entities queue
	// TODO: WHAT IF THERE ARE NO CREATED ENTITIES
	// AND THE ENTITY WE ARE PUSHING IS ALREADY
	// INSIDE THE QUEUE?
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");
	return mSignatures[entity];
}