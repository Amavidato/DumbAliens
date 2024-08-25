#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ComponentArray.h"
#include "../EcsAliases.h"

#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
	template <IsAComponentStruct T> void AddComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
		GetComponentArray<T>(true)->InsertData(entity, component);
	}
	
	template <IsAComponentStruct T> void RemoveComponent(Entity entity)
	{
		// Remove a component from the array for an entity
		GetComponentArray<T>()->RemoveData(entity);
	}
	
	template <IsAComponentStruct T> T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}
	
	void OnEntityDestroyed(Entity entity);

	// Method to get the component type associated to a component.
	template <IsAComponentStruct T> static inline ComponentType GetComponentType() noexcept
	{
		static ComponentType componentType = GetComponentType();
		return componentType;
	}

	template <IsAComponentStruct... Args>
	static Signature CreateSignature()
	{
		Signature result{};
		(result.set(GetComponentType<Args>()),...);
		return result; 
	}
	
private:
	// Map from component type to the corresponding component array
	std::unordered_map<ComponentType, std::shared_ptr<AComponentArray>> componentArrays_{};
	// The component type to be assigned to the next registered component
	ComponentType nextComponentType_{};
	// Convenience function to get statically casted pointer to the ComponentArray of type T
	template <IsAComponentStruct T> std::shared_ptr<ComponentArray<T>> GetComponentArray(bool createIfNotExists = false)
	{
		ComponentType componentType = GetComponentType<T>();
		if(createIfNotExists)
		{
			if(!componentArrays_.contains(componentType))
			{
				componentArrays_.insert({componentType, std::make_shared<ComponentArray<T>>()});
			}
		}
		else
		{
			assert(componentArrays_.contains(componentType) && "This component type has not an array initialized");
		}

		return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[componentType]);
	}

	// Method to get a new incremental "id" every time this method is called.
	static inline ComponentType GetComponentType()
	{
		static ComponentType lastType = 0;
		return lastType++;
	}
};

#endif // COMPONENTMANAGER_H
