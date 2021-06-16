#ifndef __BE_SYSTEM_H__
#define __BE_SYSTEM_H__

#include <vector>

#include "utils/Globals.h"

namespace BE
{

class Archetype;

struct ISystem
{
	ISystem(Signature s) : signature(s) {}
	virtual ~ISystem() {}
	virtual void update(const std::vector<Archetype *> &archtypes) = 0;
	virtual void render(const std::vector<Archetype *> &archtypes) = 0;

	Signature signature;
};

template<typename ...Queries>
struct System : public ISystem
{
	System() : ISystem(genSignature<Queries...>()) {}
	virtual ~System() {}

	virtual void update(const std::vector<Archetype *> &archtypes) = 0;
	virtual void render(const std::vector<Archetype *> &archtypes) = 0;
};

}

#endif // !__BE_SYSTEM_H__
