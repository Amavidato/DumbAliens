#include "BulletAutodestructionSystem.h"
#include "../Components.h"
#include "../../ecs_core/EcsManager.h"
#include "../../ecs_core/commandBuffer/EcsCommandBuffer.h"

void BulletAutodestructionSystem::OnCreate()
{
	signature = EcsManager::CreateSignature<BulletTag, Timer>();
}

void BulletAutodestructionSystem::OnUpdate(float deltaTime, EcsManager* ecsManager)
{
	EcsCommandBuffer* ecb = new EcsCommandBuffer(std::shared_ptr<EcsManager>(ecsManager));
	for(auto bullet : entities)
	{
		auto timer = ecsManager->GetComponent<Timer>(bullet);
		bool mustBeDestroied = timer.elapsedTimeInSeconds > timer.durationInSeconds;
		if (mustBeDestroied) {
			ecb->DestroyEntity(bullet);
		}
	}
	ecb->Execute();
}
