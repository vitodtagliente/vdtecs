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

	template <typename S, typename C>
	class System : public ISystem
	{
	public:

		class Component
		{
		public:

			// type aliases
			using data_t = C;
			using entity_id_t = Entity::id_t;
			using id_t = std::uint32_t;
			using system_t = S;

			Component(const id_t id, const entity_id_t entity_id, const data_t& data)
				: m_id(id)
				, m_entity_id(entity_id)
				, m_data(data)
			{}

			// returns the component id
			inline id_t id() const { return m_id; }
			// returns the entity id
			inline entity_id_t entity_id() const { return m_entity_id; }
			// returns the component data
			inline data_t& data() { return m_data; }
			inline const data_t& data() const { return m_data; }
			// returns the component type id
			static std::size_t type_id() { return s_type_id; }

		private:

			// component id
			id_t m_id;
			// entity id
			entity_id_t m_entity_id;
			// component's data
			data_t m_data;
			// component type id
			static std::size_t s_type_id;
		};

		System()
			: ISystem()
		{

		}

		// returns the system instance
		static S& instance() { return s_instance; }
		// returns the system type id
		static std::size_t type_id() { return s_type_id; }

		virtual void init() override {}
		
		virtual void update(const float delta_time) override
		{

		}

		virtual void uninit() override {}

		template <typename... P>
		Component& addComponent(const Entity& entity, P... args)
		{
			m_components.push_back(Component{ 0, entity.id(), C{std::forward<P>(args)...} });
			return m_components.front();
		}

		template <typename... P>
		Component& addComponent(const Entity::id_t id, P... args)
		{
			m_components.push_back(Component{ 0, id, C{std::forward<P>(args)...} });
			return m_components.front();
		}

		// retrieve all components
		inline std::vector<Component>& components() { return m_components; }
		inline const std::vector<Component>& components() const { return m_components; }

	private:

		// list of components
		std::vector<Component> m_components;
		// system static instance
		static S s_instance;
		// system type id
		static std::size_t s_type_id;
	};

	template <typename S, typename C>
	S System<S, C>::s_instance{};

	template <typename S, typename C>
	std::size_t System<S, C>::s_type_id = typeid(S).hash_code();

	template <typename S, typename C>
	std::size_t System<S, C>::Component::s_type_id = typeid(S).hash_code();

	/*
	template <class T>
	class System : public ISystem
	{
	public:

		// using iterator = std::vector<T>::iterator;
		// using const_iterator = std::vector<T>::const_iterator;
		using component_t = T;

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

		// const_iterator begin() const noexcept
		// {
		// 	return m_components.begin();
		// }
		// 
		// const_iterator end() const noexcept
		// {
		// 	return m_components.end();
		// }

	protected:

		virtual void each(T& component, const float delta_time) = 0;

	private:

		// list of all components
		std::vector<T> m_components;
		// lookup table with maps entities with their components
		// std::unordered_map<entity_id_t, component_t::id_t> m_lookup;
	};
	*/
}