#pragma once
#ifndef ECSALIASES_H
#define ECSALIASES_H

#include <cstdint>
#include <bitset>

//type aliases
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

//Define the maximum number of Entities we can store
constexpr Entity MAX_ENTITIES = 100000;


//Define the maximum number of Component types we can have
//in a single Entity.
const ComponentType MAX_COMPONENTS = 32;
/*
 * Define a bitset of Components. It will be used
 * to check if an Entity has a certain Component or not

 * Ex:
 * Having MAX_COMPONENTS = 10
 * and having an Entity with the following Components:
 * Transform [with typeID = 0], Rigidbody  [with typeID = 2], MeshRenderer [with typeID = 5]
 * the bitset of Components of this Entity will be:
 * [1,0,1,0,0,1,0,0,0,0]
*/
using Signature = std::bitset<MAX_COMPONENTS>;

template <typename T>
concept SimpleStruct = requires
{
	std::is_trivial_v<T> && std::is_standard_layout_v<T>;
};

#define TEMPLATE_REQUIRING_T_IS_STRUCT template <typename T> requires SimpleStruct<T>

#endif // ECSALIASES_H