#include "EcsCommandBuffer.h"
#include "EcsCommands.h"

EcsCommandBuffer::EcsCommandBuffer(std::shared_ptr<EcsManager> ecsManager)
{
	this->ecsManager_ = ecsManager;
}

void EcsCommandBuffer::Execute()
{
	for(auto commandIterator = commands_.begin(); commandIterator != commands_.end();)
	{
		(*commandIterator)->Execute(this->ecsManager_.get());
		commands_.erase(commandIterator++);
	}
}
