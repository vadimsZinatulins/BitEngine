#ifndef __BE_ECS_H__
#define __BE_ECS_H__

#include <memory>
#include <unordered_map>
#include <vector>

#include "Utils/Globals.h"
#include "Entity.h"
#include "System.h"
#include "Archetype.h"

namespace BE
{

class ECS
{
public:
	ECS() {};
	~ECS()
	{
		for (auto const &pair : m_archetypes)
		{
			delete pair.second;
		}
	};

	template<typename ...Components>
	std::shared_ptr<Entity> newEntity(Components ...components)
	{
		Signature signature = genSignature<Components...>();
		Archetype *archetype = findArchetype<Components...>(signature);
		std::shared_ptr<Entity> entity = std::make_shared<Entity>();
		entity->signature = signature;
		archetype->trackEntity(entity, components...);

		return entity;
	}

	void deleteEntity(std::shared_ptr<Entity> entity)
	{
		auto ptr = m_archetypes.find(entity->signature);
		if (ptr != m_archetypes.end())
		{
			ptr->second->untrackEntity(entity);
		}
	}

	template<typename ...Components>
	void addComponents(std::shared_ptr<Entity> entity)
	{
		Signature signature = entity->signature;
		(..., signature.set(Utils::componentTypeId<Components>(), true));
		m_archetypes.find(entity->signature)->second->untrackEntity(entity);
		auto ptr = m_archetypes.find(signature);
		if (ptr == m_archetypes.end())
		{
			Archetype *archetype = Archetype::newArchetype(m_archetypes.find(entity->signature)->second);
			auto notCreate = []() {};
			(..., (!entity->signature[Utils::componentTypeId<Components>()] ? (archetype->m_components[Utils::componentTypeId<Components>()] = new ComponentArray<Components>()) : nullptr));

			archetype->trackEntity(entity);
			m_archetypes.insert({ signature, archetype });

			for (auto &pair : m_systems)
			{
				if ((pair.first->signature & signature) == pair.first->signature)
				{
					pair.second.push_back(archetype);
				}
			}
		}
		else
		{
			ptr->second->trackEntity(entity);
		}

		entity->signature = signature;
	}

	template<typename ...Components>
	void removeComponents(std::shared_ptr<Entity> entity)
	{
		Signature signature = entity->signature;
		(..., signature.set(Utils::componentTypeId<Components>(), false));
		m_archetypes.find(entity->signature)->second->untrackEntity(entity);
		auto ptr = m_archetypes.find(signature);
		if (ptr == m_archetypes.end())
		{
			Archetype *archetype = Archetype::newArchetype(m_archetypes.find(entity->signature)->second, signature);

			archetype->trackEntity(entity);
			m_archetypes.insert({ signature, archetype });

			for (auto &pair : m_systems)
			{
				if ((pair.first->signature & signature) == pair.first->signature)
				{
					pair.second.push_back(archetype);
				}
			}
		}
		else
		{
			ptr->second->trackEntity(entity);
		}

		entity->signature = signature;
	}

	template<typename T>
	void registerSystem()
	{
		m_systems.push_back(std::make_pair<ISystem *, std::vector<Archetype *>>(new T(), {}));
	}
private:
	friend class Engine;

	void update()
	{
		for (auto const &pair : m_systems)
		{
			pair.first->update(pair.second);
		}
	}

	void render()
	{
		for (auto const &pair : m_systems)
		{
			pair.first->render(pair.second);
		}
	}

	template<typename ...Components>
	Archetype *findArchetype(Signature signature)
	{
		auto ptr = m_archetypes.find(signature);
		if (ptr == m_archetypes.end())
		{
			Archetype *archetype = Archetype::newArchetype<Components...>();
			m_archetypes.insert({ signature, archetype });

			for (auto &pair : m_systems)
			{
				if ((pair.first->signature & signature) == pair.first->signature)
				{
					pair.second.push_back(archetype);
				}
			}

			return archetype;
		}

		return ptr->second;
	}

	std::unordered_map<Signature, Archetype *> m_archetypes{};
	std::vector<std::pair<ISystem *, std::vector<Archetype *>>> m_systems;
};

}

#endif // !__BE_ECS_H__
