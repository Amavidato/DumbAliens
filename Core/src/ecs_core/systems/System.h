#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H


#include "../EcsAliases.h"
#include <set>


class EcsManager;

class ASystem
{
public:
	virtual ~ASystem() = default;
	// Here we have to define the signature of the system
	virtual void OnCreate() = 0;
	// Here we have to define the behaviour of the system
	virtual void OnUpdate(float deltaTime, EcsManager* ecsManager) = 0;
	int GetId() const {return id_;}
	Signature GetSignature() const { return signature;}
	std::set<Entity> entities;

protected:
	Signature signature;
private:
	static int GetSystemId()
	{
		static int lastId = 0;
		return lastId++;
	}

	int id_ = GetSystemId();
};
#endif // SYSTEM_H