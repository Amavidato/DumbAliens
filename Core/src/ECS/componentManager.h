#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ecsAliases.h"
#include "componentArray.h"

#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
	TEMPLATE_REQUIRING_T_IS_STRUCT void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

		// Add this component type to the component type map
		mComponentTypes.insert({typeName, mNextComponentType});

		// Create a ComponentArray pointer and add it to the component arrays map
		mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

		// Increment the value so that the next component registered will be different
		++mNextComponentType;
	}
	
	TEMPLATE_REQUIRING_T_IS_STRUCT ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return mComponentTypes[typeName];
	}
	
	TEMPLATE_REQUIRING_T_IS_STRUCT void AddComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
		GetComponentArray<T>()->InsertData(entity, component);
	}
	
	TEMPLATE_REQUIRING_T_IS_STRUCT void RemoveComponentType(Entity entity)
	{
		// Remove a component from the array for an entity
		GetComponentArray<T>()->RemoveData(entity);
	}
	
	TEMPLATE_REQUIRING_T_IS_STRUCT T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}
	
	TEMPLATE_REQUIRING_T_IS_STRUCT void EntityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : mComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}
	
private:
	// Map from type string pointer to a component type
	std::unordered_map<const char*, ComponentType> mComponentTypes{};
	// Map from type string pointer to a component type
	std::unordered_map<const char*, std::shared_ptr<AComponentArray>> mComponentArrays{};
	// The component type to be assigned to the next registered component
	ComponentType mNextComponentType{};
	// Convenience function to get statically casted pointer to the ComponentArray of type T
	TEMPLATE_REQUIRING_T_IS_STRUCT std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}
};

#endif // COMPONENTMANAGER_H
