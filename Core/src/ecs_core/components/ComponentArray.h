#pragma once
#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "Component.h"
#include "../EcsAliases.h"
#include <cassert>
#include <unordered_map>
#include <ranges>
#include <unordered_set>

// An abstraction is required so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class AComponentArray
{
public:
	virtual ~AComponentArray() = default;
	inline virtual void OnEntityDestroyed(Entity entity) = 0;
};

template <typename T>
concept IsAComponentStruct = std::is_base_of_v<AComponent, T> && std::is_trivial_v<T> && std::is_standard_layout_v<T>;

// A template for a ComponentArray. There will be one
// instance of it for each component type.
template <IsAComponentStruct T>
class ComponentArray : public AComponentArray
{
public:
	
	bool HasComponent(Entity entity) const
	{
		return entityToIndexMap_.contains(entity);
	}
	
	void InsertData(Entity entity, T component)
	{
		assert(!entityToIndexMap_.contains(entity)
			&& "Entity already has a component of this type");

		size_t newIndex = size_++;
		entityToIndexMap_[entity] = newIndex;
		indexToEntityMap_[newIndex] = entity;
		componentArray_[newIndex] = component;
	}
	
	void RemoveData(Entity entity)
	{
		assert(entityToIndexMap_.contains(entity)
			&& "Entity doesn't have a component of this type");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = entityToIndexMap_[entity];
		size_t indexOfLastElement = --size_;
		componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
		entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
		indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;

		entityToIndexMap_.erase(entity);
		indexToEntityMap_.erase(indexOfLastElement);
	}
	
	T& GetData(Entity entity)
	{
		assert(entityToIndexMap_.contains(entity)
			&& "Entity doesn't have a component of this type");
		return componentArray_[entityToIndexMap_[entity]];
	}
	
	void OnEntityDestroyed(Entity entity) override
	{
		if(entityToIndexMap_.contains(entity))
		{
			// Remove the entity's component if it exists
			RemoveData(entity);
		}
	}

	std::unordered_set<Entity> GetEntities()
	{
		auto keys = std::views::keys(entityToIndexMap_);
		std::unordered_set<Entity> entities{ keys.begin(), keys.end() };
		return entities;
	}
	
private:
	// The packed array of components of type T (one for each entity)
	std::array<T,MAX_ENTITIES> componentArray_;
	// Map to get component array's index from entity ID
	std::unordered_map<Entity, size_t> entityToIndexMap_;
	// Map to get entity ID from component array's index
	std::unordered_map<size_t, Entity> indexToEntityMap_;

	// Total size of valid entries in the array.
	size_t size_;
};
#endif // COMPONENTARRAY_H