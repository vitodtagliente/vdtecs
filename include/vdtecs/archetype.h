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
		std::unordered_set<id_t> entities;
	};

	class ArchetypeTable
	{
	public:
		template <typename ...C>
		static Archetype& emplace(C...components);

		template <typename ...C>
		static Archetype* const find();
		static Archetype* const find(const std::unordered_set<id_t>& components);

	private:
		static std::vector<Archetype> s_archetypes;
		// archetype, entities
		static std::unordered_map<id_t, std::vector<id_t>> s_entities;
	};

	template <typename ...C>
	Archetype& ArchetypeTable::emplace(C...components)
	{
		Archetype type;
		type.components = { Component<C>::id()... };
		s_archetypes.push_back(type);
		return s_archetypes.back();
	}

	template <typename ...C>
	Archetype* const ArchetypeTable::find()
	{
		return find({ Component<C>::id()... });
	}
}