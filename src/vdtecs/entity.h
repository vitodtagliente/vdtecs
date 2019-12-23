/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <vector>

namespace ecs
{
	class Entity final
	{
	public:

		class Manager
		{
		public:

			using id_t = std::uint32_t;

			static constexpr id_t INVALID_ID = 0;

			Manager()
				: m_counter(INVALID_ID)
				, m_entities()
				, m_pendingRemoveEntities()
				, m_unusedIds()
			{}

			Entity create()
			{
				id_t assigned_id = INVALID_ID;

				if (m_unusedIds.size() > 0)
				{
					assigned_id = m_unusedIds.front();
					m_unusedIds.pop_back();
				}
				else
				{
					assigned_id = ++m_counter;
				}

				m_entities.push_back(Entity{ assigned_id });
				return m_entities.front();
			}

			const std::vector<Entity>& all() const
			{
				return m_entities;
			}

			Entity find(const id_t id) const
			{
				const auto it = std::find_if(
					m_entities.begin(),
					m_entities.end(),
					[id](const Entity& entity) { return entity.id() == id; }
				);
				
				if (it != m_entities.end())
				{
					return *it;
				}
				return Entity{ INVALID_ID };
			}

			void remove(const id_t id)
			{
				const auto it = std::find_if(
					m_entities.begin(),
					m_entities.end(),
					[id](const Entity& entity) { return entity.id() == id; }
				);
				
				if (it != m_entities.end())
				{
					m_pendingRemoveEntities.push_back(*it);
					m_entities.erase(it);
				}
			}

			void reset()
			{
				m_counter = INVALID_ID;
				m_entities.clear();
				m_unusedIds.clear();
				m_pendingRemoveEntities.clear();
			}

		private:

			// id counter
			id_t m_counter;
			// list of entities
			std::vector<Entity> m_entities;
			// list of ids pending to be removed
			std::vector<Entity> m_pendingRemoveEntities;
			// list of unused ids
			std::vector<id_t> m_unusedIds;
		};
		
		using id_t = Manager::id_t;

		Entity(const id_t id)
			: m_id(id)
		{ }

		inline id_t id() const { return m_id; }
		
		operator bool() const
		{
			return isValid();
		}

		bool isValid() const
		{
			return m_id != Manager::INVALID_ID;
		}

		void invalidate()
		{
			m_id = Manager::INVALID_ID;
		}

		void destroy()
		{
			if (isValid())
			{
				// TODO
				// remove from systems
				s_manager.remove(m_id);
				m_id = Manager::INVALID_ID;
			}
		}

		inline bool operator== (const Entity& other) const
		{ 
			return m_id == other.m_id; 
		}

		inline bool operator!= (const Entity& other) const
		{ 
			return m_id != other.m_id; 
		}

		template <typename T, typename... P>
		inline T& addComponent(P... args)
		{
			// TODO
			return T{};
		}

		static Entity create()
		{
			return s_manager.create();
		}

		static Entity find(const id_t id)
		{
			return s_manager.find(id);
		}

		static std::vector<Entity> all()
		{
			return s_manager.all();
		}

		// get the Entity Manager
		static Manager manager()
		{
			return s_manager;
		}

		// invalid entity definition
		static Entity INVALID;

	private:

		// entity id
		id_t m_id;
		// entity manager
		static Manager s_manager;
	};

	// Invalid Entity
	Entity Entity::INVALID{ Manager::INVALID_ID };
	// Entity Manager
	Entity::Manager Entity::s_manager{};
}