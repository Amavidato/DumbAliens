#pragma once
#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "ecsAliases.h"
#include <cassert>
#include <unordered_map>

// An abstraction is required so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class AComponentArray
{
public:
	virtual ~AComponentArray() = default;
	inline virtual void EntityDestroyed(Entity entity) = 0;
};

// A template for a ComponentArray. There will be one
// instance of it for each component type.
TEMPLATE_REQUIRING_T_IS_STRUCT
class ComponentArray : public AComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()
			&& "Entity already has a component of this type");

		size_t newIndex = mSize++;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentArray[newIndex] = component;
	}
	
	void RemoveData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()
			&& "Entity doesn't have a component of this type");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = --mSize;
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);
	}
	
	T& GetData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()
			&& "Entity doesn't have a component of this type");
		return mComponentArray[mEntityToIndexMap[entity]];
	}
	
	void EntityDestroyed(Entity entity) override
	{
		if(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
		{
			// Remove the entity's component if it exists
			RemoveData(entity);
		}
	}
private:
	// The packed array of components of type T (one for each entity)
	std::array<T,MAX_ENTITIES> mComponentArray;
	// Map to get component array's index from entity ID
	std::unordered_map<Entity, size_t> mEntityToIndexMap;
	// Map to get entity ID from component array's index
	std::unordered_map<size_t, Entity> mIndexToEntityMap;

	// Total size of valid entries in the array.
	size_t mSize;
};
#endif // COMPONENTARRAY_H