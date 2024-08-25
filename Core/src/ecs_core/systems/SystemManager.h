#pragma once
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "System.h"
#include "../EcsAliases.h"
#include <memory>
#include <unordered_map>
#include <cassert>

template <typename T>
concept IsASystem = std::is_base_of_v<ASystem, T>;

class SystemManager
{
public:
	
	template <IsASystem T>
	void RegisterSystem()
	{
		std::shared_ptr<T> aSystemPtr = std::make_shared<T>();
		SystemID systemID = aSystemPtr->GetID();
		assert(!systems_.contains(systemID) && "Trying to add a System that is already registered");
		
		systems_.insert({systemID, aSystemPtr});
		aSystemPtr->OnCreate();
	}
	
	void OnEntityDestroyed(Entity entity)
	{
		// Erase a destroyed entity from all systems
		for (auto const& pair : systems_)
		{
			auto const& system = pair.second;

			// mEntities is a set, so no check needed
			system->entities.erase(entity);
		}
	}

	void OnEntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for(auto const& pair : systems_)
		{
			SystemID systemID = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = system->GetSignature();

			// System signature matches entity new signature
			if((entitySignature & systemSignature) == systemSignature)
			{
				system->entities.insert(entity);
			}
			// System signature does NOT match entity signature
			else
			{
				system->entities.erase(entity);
			}
		}
	}
	
private:
	// Map from system type string pointer to a system pointer
	std::unordered_map<SystemID, std::shared_ptr<ASystem>> systems_{};
};

#endif // SYSTEMMANAGER_H