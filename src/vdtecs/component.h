/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <cstdint>
#include "entity.h"

namespace ecs
{
	template <typename T>
	class Component
	{
	public:

		using id_t = std::uint32_t;
		using entity_id_t = Entity::id_t;
		using type = T;

		Component()
			: m_id()
			, m_entity()
		{}

		inline id_t id() const { return m_id; }
		inline entity_id_t entity() const { return m_entity; }

		bool operator== (const Component<T>& component) const
		{
			return m_id == component.m_id;
		}

		bool operator!= (const Component<T>& component) const
		{
			return m_id != component.m_id;
		}

	private:

		// component id
		id_t m_id;
		// entity id
		entity_id_t m_entity;
	};
}