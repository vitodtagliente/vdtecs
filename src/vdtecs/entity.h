/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <algorithm>
#include <map>
#include <vector>
#include "id_manager.h"

namespace ecs
{
	class Entity final
	{
	public:

		using id_t = IdManager::id_t;

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
			return m_id != IdManager::INVALID_ID;
		}

		void invalidate()
		{
			m_id = IdManager::INVALID_ID;
		}

		void destroy()
		{
			if (isValid())
			{
				// TODO
				// remove from systems
				s_manager.remove(m_id);
				m_id = IdManager::INVALID_ID;
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

		static Entity create()
		{
			return Entity{ s_manager.next() };
		}

		static Entity find(const id_t id)
		{
			return Entity{ s_manager.find(id) };
		}

		static std::vector<Entity> all()
		{
			std::vector<Entity> entities;
			const std::vector<IdManager::id_t>& ids = s_manager.all();
			entities.reserve(ids.size());
			std::transform(
				ids.begin(), 
				ids.end(),
				std::back_inserter(entities), 
				[](const IdManager::id_t id) { return Entity{ id }; });
			return entities;
		}

		static Entity INVALID;

	private:

		// entity id
		id_t m_id;
		// static id manager
		static IdManager s_manager;
	};

	Entity Entity::INVALID{ IdManager::INVALID_ID };
	IdManager Entity::s_manager{};
}