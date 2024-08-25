#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include "../EcsAliases.h"
#include <set>

using SystemID = std::size_t;

class ASystem
{
public:
	virtual ~ASystem() = default;
	// Here we have to define the signature of the system
	virtual void OnCreate() = 0;
	// Here we have to define the behaviour of the system
	virtual void OnUpdate() = 0;
	SystemID GetID() const {return id_;}
	Signature GetSignature() const { return signature;}
	std::set<Entity> entities;

protected:
	Signature signature;

private:
	static SystemID GetSystemID()
	{
		static SystemID lastID = 0;
		return lastID++;
	}

	SystemID id_ = GetSystemID();
};


#endif // SYSTEM_H