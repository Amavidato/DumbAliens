#pragma once
#ifndef ECSCOMMANDS_H
#define ECSCOMMANDS_H

class EcsCommand
{
public:
	virtual ~EcsCommand() = default;
	virtual void Execute(EcsManager* ecsManager) = 0;
};

class DestroyEntityCommand : public EcsCommand
{
public:
	DestroyEntityCommand(Entity e) : entity_(e) {}
	void Execute(EcsManager* ecsManager) override
	{
		ecsManager->DestroyEntity(entity_);
	}
private:
	Entity entity_;
};

template<IsAComponentStruct T>
class AddComponentCommand : public EcsCommand
{
public:
	AddComponentCommand(Entity e, T c) : entity_(e), component_(c) {}
	void Execute(EcsManager* ecsManager) override
	{
		ecsManager->AddComponent(entity_, component_);
	}
private:
	Entity entity_;
	T component_;
};

#endif // ECSCOMMANDS_H
