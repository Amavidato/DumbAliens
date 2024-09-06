#pragma once
#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "EcsAliases.h"
#include "components/ComponentManager.h"
#include "entities/EntityManager.h"
#include "systems/SystemManager.h"
#include <memory>

template <typename T>
concept IsAComponentTag = IsAComponentStruct<T> && std::is_empty_v<T>;

class EcsManager
{
public:
	EcsManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void UpdateSystems(float deltaTime);
	
	template<IsAComponentStruct T>
	bool HasComponent(Entity entity)
	{
		return componentManager_->HasComponent<T>(entity);
	}
	
	template<IsAComponentStruct T>
	void AddComponent(Entity entity, T component)
	{
		componentManager_->AddComponent<T>(entity, component);
		ChangeEntitySignature<T>(entity, true);
	}
	
	template<IsAComponentTag T>
	void AddComponent(Entity entity)
	{
		componentManager_->AddComponent<T>(entity, T());
		ChangeEntitySignature<T>(entity, true);
	}

	template<IsAComponentStruct T>
    void RemoveComponent(Entity entity)
    {
		componentManager_->RemoveComponent<T>(entity);
		ChangeEntitySignature<T>(entity, false);
    }

	template<IsAComponentStruct T>
	T& GetComponent(Entity entity)
	{
		return componentManager_->GetComponent<T>(entity);
	}

	template<IsAComponentStruct T>
	ComponentType GetComponentType()
	{
		return componentManager_->GetComponentType<T>();
	}

	template<DerivedFromAllowedClasses T>
	void RegisterSystem(std::shared_ptr<T> aSystem)
	{
		systemManager_->RegisterSystem(aSystem);
	}

	template<IsAComponentStruct... Args>
	static Signature CreateSignature()
	{
		return ComponentManager::CreateSignature<Args...>();
	}

	template<IsAComponentStruct... Args>
	std::unordered_set<Entity> GetEntitiesWithAny()
	{
		return ((GetEntitiesWithComponentType<Args>()),...);
	}

private:
	std::unique_ptr<ComponentManager> componentManager_;
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<SystemManager> systemManager_;

	void Init();
	
	template<IsAComponentStruct T>
	void ChangeEntitySignature(Entity entity, bool addedNewComponent)
	{
		auto signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(),addedNewComponent);
		entityManager_->SetSignature(entity, signature);
		systemManager_->OnEntitySignatureChanged(entity, signature);
	}

	template <IsAComponentStruct T>
	std::unordered_set<Entity> GetEntitiesWithComponentType() {
		return componentManager_->GetEntitiesWithComponent<T>();
	}
};

#endif // ECSMANAGER_H