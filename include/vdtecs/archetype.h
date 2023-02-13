/// Copyright (c) Vito Domenico Tagliente
#pragma once 

#include <cstddef>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "component.h"
#include "id.h"

namespace ecs
{
	struct Archetype
	{
		id_t id;
		std::unordered_set<id_t> components;
	};

	class ArchetypeTable
	{
	public:

		template <typename ...C>
		static Archetype* const find();


	private:
		static std::vector<Archetype> s_archetypes;
		// archetype, entities
		static std::unordered_map<id_t, std::vector<id_t>> s_entities;
	};

	template <typename ...C>
	Archetype* const ArchetypeTable::find()
	{
		std::unordered_set<id_t> set{ Component<C>::id()... };
		const auto& it = std::find_if(
			s_archetypes.begin(),
			s_archetypes.end(),
			[&set](const Archetype& archetype) -> bool
			{
				return archetype.components = set;
			}
		);

		if (it != s_archetypes.end())
		{
			return *it;
		}
		return nullptr;
	}
}