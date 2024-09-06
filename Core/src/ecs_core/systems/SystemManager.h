#pragma once
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "System.h"
#include "SpecializedSystems.h"
#include "../EcsAliases.h"
#include <cassert>
#include <memory>

//TODO: investigate forward declaration vs include header
// Include doesn't work. Probably there is a ciclic depencency
//#include "../EcsManager.h"
class EcsManager;

// Concept to check if a type is derived from C1, C2, or C3
template <typename T>
concept DerivedFromAllowedClasses =
	std::derived_from<T, InitializationSystem>
	|| std::derived_from<T, LogicSystem>
	|| std::derived_from<T, RenderingSystem>;

	
class SystemManager
{
public:
	void UpdateSystems(float deltaTime, EcsManager* ecsManager);

	template<DerivedFromAllowedClasses T>
	void RegisterSystem(std::shared_ptr<T> aSystem)
	{
		SystemID systemID = aSystem->GetID();
		assert(!systemsSet_.contains(aSystem) && "Trying to add a System that is already registered");
		systemsSet_.insert(aSystem);
		aSystem->OnCreate();
	}
	
	void OnEntityDestroyed(Entity entity)
	{
		// Erase a destroyed entity from all systems
		for (auto const& system : systemsSet_)
		{
			// mEntities is a set, so no check needed
			system->entities.erase(entity);
		}
	}

	void OnEntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for(auto const& system : systemsSet_)
		{
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

	static bool STOP_SYSTEMS_EXECUTION;
	
private:
	// Map from system type string pointer to a system pointer
	//std::unordered_map<SystemID, std::shared_ptr<ASystem>> systems_{};

	struct Comparator
	{
		bool operator()(const std::shared_ptr<ASystem>& a, const std::shared_ptr<ASystem>& b) const
		{
			if (dynamic_cast<InitializationSystem*>(a.get()) && dynamic_cast<LogicSystem*>(b.get())) {
				return true;
			}
			if (dynamic_cast<InitializationSystem*>(a.get()) && dynamic_cast<RenderingSystem*>(b.get())) {
				return true;
			}
			if (dynamic_cast<LogicSystem*>(a.get()) && dynamic_cast<RenderingSystem*>(b.get())) {
				return true;
			}
			if(dynamic_cast<InitializationSystem*>(a.get()) && dynamic_cast<InitializationSystem*>(b.get())
				|| dynamic_cast<LogicSystem*>(a.get()) && dynamic_cast<LogicSystem*>(b.get())
				|| dynamic_cast<RenderingSystem*>(a.get()) && dynamic_cast<RenderingSystem*>(b.get()))
			{
				return a->GetID() < b->GetID();
			}
			// For other cases, we could either consider them equal or use a different criterion.
			return false;
		}
	};
	
	std::set<std::shared_ptr<ASystem>, Comparator> systemsSet_{};
};

#endif // SYSTEMMANAGER_H