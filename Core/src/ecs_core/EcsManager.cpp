#include "EcsManager.h"

EcsManager::EcsManager()
{
	Init();
}

Entity EcsManager::CreateEntity()
{
	return entityManager_->CreateEntity();
}

void EcsManager::DestroyEntity(Entity entity)
{
	entityManager_->DestroyEntity(entity);
	componentManager_->OnEntityDestroyed(entity);
	systemManager_->OnEntityDestroyed(entity);
}

void EcsManager::Init()
{
	componentManager_ = std::make_unique<ComponentManager>();
	entityManager_ = std::make_unique<EntityManager>();
	systemManager_ = std::make_unique<SystemManager>();
}
