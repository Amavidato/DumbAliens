#include "ComponentManager.h"

void ComponentManager::OnEntityDestroyed(Entity entity)
{
	// Notify each component array that an entity has been destroyed
	// If it has a component for that entity, it will remove it
	for (auto const& pair : componentArrays_)
	{
		auto const& component = pair.second;

		component->OnEntityDestroyed(entity);
	}
}
