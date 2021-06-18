#ifndef __BE_ENTITY_H__
#define __BE_ENTITY_H__

#include <memory>

#include "utils/Globals.h"
namespace BE
{

struct Entity
{
	std::size_t index;
	Signature signature;
};

using EntityPtr = std::shared_ptr<Entity>;

}

#endif // !__BE_ENTITY_H__
