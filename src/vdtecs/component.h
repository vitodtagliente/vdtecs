/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <cstdint>
#include <typeinfo>
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

		static std::size_t type_id()
		{
			return s_type_id;
		}

	private:

		// component id
		id_t m_id;
		// entity id
		entity_id_t m_entity;

		// component type id
		static std::size_t s_type_id;
	};

	template <typename T>
	std::size_t Component<T>::s_type_id = typeid(T).hash_code();
}