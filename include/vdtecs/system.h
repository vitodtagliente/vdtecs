/// Copyright (c) Vito Domenico Tagliente

#pragma once 

#include <cassert>
#include <cstddef>
#include <vector>
#include "entity.h"
#include "isystem.h"

namespace ecs
{	
	template <typename S, typename C>
	class System : public ISystem
	{
	public:

		/// Component class definition
		/// It is responsible of storing info about it's owner (entity)
		/// and data
		class Component
		{
		public:

			// type aliases
			using Data = C;
			using entity_id_t = Entity::id_t;
			using id_t = std::uint32_t;
			using System = S;

			static constexpr id_t INVALID_ID = 0;

			Component(const id_t id, const entity_id_t entity_id, const Data& data)
				: m_id(id)
				, m_entity_id(entity_id)
				, m_data(data)
			{}

			inline bool is_valid() const { return m_id != INVALID_ID; }
			inline operator bool() const { return is_valid(); }
			inline void invalidate() { m_id = INVALID_ID; }

			// returns the component id
			inline id_t id() const { return m_id; }
			// returns the entity id
			inline entity_id_t entity_id() const { return m_entity_id; }
			// returns the component data
			inline Data& data() { return m_data; }
			inline const Data& data() const { return m_data; }
			// returns the component type id
			static std::size_t type_id() { return s_type_id; }

			inline bool operator== (const Component& component) const
			{
				return m_id == component.m_id;
			}

			inline bool operator!= (const Component& component) const
			{
				return m_id != component.m_id;
			}

		private:

			// component id
			id_t m_id;
			// entity id
			entity_id_t m_entity_id;
			// component's data
			Data m_data;
			// component type id
			static std::size_t s_type_id;
		};

		System() = default;

		// type aliases
		using Data = C;
		using component_id_t = typename Component::id_t;

		// returns the system instance
		static S& instance() { return s_instance; }
		// returns the system type id
		static std::size_t type_id() { return s_type_id; }

		virtual void init() override {}
		
		virtual void update(const float delta_time) override
		{

		}

		virtual void uninit() override 
		{
			m_components.clear();
		}
		
		virtual void removeEntity(const Entity::id_t entity_id) override
		{
			for (auto it = m_components.begin(); it != m_components.end(); ++it)
			{
				if (it->entity_id() == entity_id)
				{
					m_components.erase(it);
				}
			}
		}

		virtual bool containsEntity(const Entity::id_t entity_id) override
		{
			return getComponent(entity_id) != nullptr;
		}

		template <typename... P>
		Component& addComponent(const Entity& entity, P... args)
		{
			return addComponent(entity.id(), std::forward<P>(args)...);
		}

		template <typename... P>
		Component& addComponent(const Entity::id_t id, P... args)
		{
			m_components.push_back(Component{ ++m_id_counter, id, C{std::forward<P>(args)...} });
			return m_components.front();
		}

		// retrieve all components
		inline std::vector<Component>& components() { return m_components; }
		inline const std::vector<Component>& components() const { return m_components; }

		Component* const getComponentById(const component_id_t id)
		{
			for (Component& component : m_components)
			{
				if (component.id() == id)
					return &component;
			}
			return nullptr;
		}

		Component* const getComponent(const Entity& entity) { return getComponent(entity.id()); }

		Component* const getComponent(const Entity::id_t id)
		{
			for (Component& component : m_components)
			{
				if (component.entity_id() == id)
					return &component;
			}
			return nullptr;
		}

		std::vector<Component*> getComponents(const Entity& entity) 
		{ 
			return getComponents(entity.id()); 
		}

		std::vector<Component*> getComponents(const Entity::id_t id)
		{
			std::vector<Component*> components;
			for (Component& component : m_components)
			{
				if (component.entity_id() == id)
					components.push_back(&component);
			}
			return components;
		}

		void removeComponent(const Entity& entity)
		{
			removeComponent(entity.id());
		}

		void removeComponent(const Entity::id_t entity_id)
		{
			const auto it = std::find_if(
				m_components.begin(),
				m_components.end()
				[id = entity_id](const Component& component)
				{
					return component.entity_id() == id;
				}
			);
			m_components.erase(it);
		}

	private:

		// list of components
		std::vector<Component> m_components;
		// components id counter
		component_id_t m_id_counter;
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
}