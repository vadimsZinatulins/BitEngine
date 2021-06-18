#ifndef __BE_ACHETYPE_H__
#define __BE_ACHETYPE_H__

#ifndef MAX_NUM_ENTITIES
#define MAX_NUM_ENTITIES 256
#endif

#include <unordered_map>
#include <memory>

#include "Entity.h"
#include "ComponentArray.h"
#include "Utils/Globals.h"

namespace BE
{

class Archetype;

using ArchetypePtr = std::shared_ptr<Archetype>;

class Archetype
{
public:
	Archetype() : m_count(0), m_entities(new EntityPtr[MAX_NUM_ENTITIES]) {}
	~Archetype()
	{
		for (auto const &pair : m_components)
		{
			delete pair.second;
		}

		delete[] m_entities;

		m_count = 0;
	}

	template<typename ...Components>
	static inline ArchetypePtr newArchetype()
	{
		ArchetypePtr archetype = std::make_shared<Archetype>();

		(..., archetype->m_components.insert({ Utils::componentTypeId<Components>(), new ComponentArray<Components>() }));

		return archetype;
	}

	template<typename ...Components>
	static inline ArchetypePtr newArchetype(std::tuple<Components...>)
	{
		return newArchetype<Components...>();
	}

	static inline ArchetypePtr newArchetype(Archetype *original)
	{
		ArchetypePtr archetype = std::make_shared<Archetype>();
		for (auto const &pair : original->m_components)
		{
			archetype->m_components[pair.first] = pair.second->copy();
		}
		return archetype;
	}

	static inline ArchetypePtr newArchetype(Archetype *original, Signature signature)
	{
		ArchetypePtr archetype = std::make_shared<Archetype>();
		for (auto const &pair : original->m_components)
		{
			if (signature[pair.first])
			{
				archetype->m_components[pair.first] = pair.second->copy();
			}
		}
		return archetype;
	}

	template<typename Component>
	inline Component *getComponentArray()
	{
		return static_cast<ComponentArray<Component>*>(m_components[Utils::componentTypeId<Component>()])->components;
	}

	template<typename ...Components>
	void trackEntity(EntityPtr entity, Components... components)
	{
		m_entities[m_count] = entity;
		entity->index = m_count;
		(..., (static_cast<ComponentArray<Components>*>(m_components[Utils::componentTypeId<Components>()])->components[m_count] = components));
		m_count++;
	}

	void untrackEntity(EntityPtr entity)
	{
		m_count--;
		m_entities[m_count]->index = entity->index;
		m_entities[entity->index] = m_entities[m_count];
	}

	inline std::size_t count() const { return m_count; }
private:
	friend class ECS;

	std::size_t m_count;
	std::unordered_map<std::size_t, IComponentArray *> m_components;
	EntityPtr *m_entities;
};

}

#endif // !__BE_ACHETYPE_H__
