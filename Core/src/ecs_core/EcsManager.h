#pragma once
#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "EcsAliases.h"
#include "components/ComponentManager.h"
#include "entities/EntityManager.h"
#include "systems/SystemManager.h"
#include <memory>

class EcsManager
{
public:
	EcsManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void UpdateSystems(float deltaTime);
	
	template<IsAComponentStruct T>
	void AddComponent(Entity entity, T component)
	{
		componentManager_->AddComponent<T>(entity, component);
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
};

#endif // ECSMANAGER_H