/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <stack>
#include <vector>

#include "component.h"
#include "id.h"

namespace ecs
{
	/// An entity is basically an unsigned int 32
	/// This class wraps that number and offers functions that
	/// let the entity management easier (destroy, components, etc...)
	/// sizeof(Entity) == sizeof(std::uint32)
	/// It is not required to dynamically allocate these entities,
	/// pointers are no required, basic copies are enough to work with this class.
	class Entity final
	{
	public:
		
		/// this Manager is responsible of ids assignments
		/// moreover, it behaves as a central location in which all entities are stored (cached)
		class Manager final
		{
		public:
			Manager();

			// create a new entity, id assignment logic
			Entity create();
			// retrieve all the alive entities 
			const std::vector<Entity>& all() const;
			// find an entity
			Entity find(id_t entity_id) const;
			// remove an entity
			// (system components removement)
			void remove(id_t entity_id);
			// flush pending data
			std::vector<id_t> flush();

			// reset and clear all data
			void reset();

		private:

			// id counter
			id_t m_counter;
			// list of entities
			std::vector<Entity> m_entities;
			// list of ids pending to be removed
			std::vector<Entity> m_pendingRemoveEntities;
			// list of unused ids
			std::stack<id_t> m_unusedIds;
		};
		
		Entity(const id_t id);

		inline id_t id() const { return m_id; }		

		bool is_valid() const;
		operator bool() const { return is_valid(); }
		operator id_t() const { return m_id; }
		void invalidate();

		void destroy();

		bool operator== (const Entity& other) const;
		bool operator!= (const Entity& other) const;

		template <typename T, typename... P>
		inline T& addComponent(P... args)
		{
			return Component<T>::push_back(m_id, std::forward<P>(args)...);
		}

		template <typename T>
		inline T* const getComponent() const
		{
			return Component<T>::find(m_id);
		}

		template <typename T>
		inline void removeComponent()
		{
			Component<T>::erase(m_id);
		}

		/// facilities APIs
		static Entity create();
		static Entity find(id_t entity_id);
		static const std::vector<Entity>& all();

		// get the Entity Manager
		static Manager& manager();

		// invalid entity definition
		static Entity INVALID;

	private:

		// entity id
		id_t m_id;
		// entity manager
		static Manager s_manager;
	};
}