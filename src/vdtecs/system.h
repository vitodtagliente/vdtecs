/// Copyright (c) Vito Domenico Tagliente

#pragma once 

#include <cassert>
#include <cstddef>
#include <vector>
#include "component.h"
#include "entity.h"
#include "type_id.h"

namespace ecs
{
	class ISystem
	{
	public:

		virtual void init() = 0;
		virtual void update(const float delta_time) = 0;
		virtual void uninit() = 0;
	};

	template <class T>
	class System : public ISystem
	{
	public:

		using id_t = std::uint32_t;

		System()
			: m_components()
		{
		}

		virtual ~System() = default;

		inline const std::vector<T>& components() const 
		{ 
			return m_components; 
		}

		template <typename... P>
		inline T& addComponent(const Entity& entity, P... args)
		{
			// check if the entity is a valid one
			assert(entity.isValid());

			// only one component of the same type per entity is allowed
			// assert(m_lookup.find(t_entity) == m_lookup.end());
			// assert(m_lookup.size() == m_components.size());

			// create a new component for the given entity
			T component_to_add(std::forward<P>(args)...);
			// component_to_add.m_id = 1;
			m_components.push_back(component_to_add);

			return m_components.back();
		}

		void removeComponent(const size_t t_entity)
		{
			// auto it = m_lookup.find(t_entity);
			// if (it != m_lookup.end())
			// {
			// 	const size_t index = it->second;
			// 
			// 	if (index < m_components->size() - 1)
			// 	{
			// 		// swap out the dead element with the last one
			// 		m_components[index] = std::move(m_components.back());
			// 		m_entities[index] = m_entities.back();
			// 
			// 		// update the lookup table
			// 		m_lookup[m_entities[index]] = index;
			// 	}
			// 
			// 	// shrink the container
			// 	m_components->pop_back();
			// 	m_entities.pop_back();
			// 	m_lookup.erase(it);
			// }
		}

		inline void clear()
		{
			// m_lookup.clear();
			// m_components.clear();
			// m_entities.clear();
		}

		// system's initialization
		virtual void init() override {}

		// updating components
		virtual void update(const float delta_time) override
		{
			for (T& component : m_components)
			{
				each(component, delta_time);
			}
		}

		// system's uninitalization
		virtual void uninit() override {}

	protected:

		virtual void each(T& component, const float delta_time) = 0;

	private:

		// list of all components
		std::vector<T> m_components;
		// lookup table with maps entities with their components
		// std::unordered_map<entity_id_t, component_t::id_t> m_lookup;
	};
}