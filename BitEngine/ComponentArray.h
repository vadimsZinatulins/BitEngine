#ifndef __BE_COMPONENT_ARRAY_H__
#define __BE_COMPONENT_ARRAY_H__

#include <cstddef>

namespace BE
{

struct IComponentArray
{
	IComponentArray() = default;
	~IComponentArray() = default;

	virtual void replace(std::size_t src, std::size_t dst) = 0;
	virtual IComponentArray *copy() = 0;
};

template<typename T>
struct ComponentArray final : public IComponentArray
{
	ComponentArray() : components(new T[MAX_NUM_ENTITIES]) {}
	~ComponentArray() { delete[] components; }

	inline void replace(std::size_t src, std::size_t dst) override
	{
		components[dst] = components[src];
	}

	inline IComponentArray *copy() override
	{
		return new ComponentArray<T>();
	}

	T *components;
};

}

#endif // !__BE_COMPONENT_ARRAY_H__
