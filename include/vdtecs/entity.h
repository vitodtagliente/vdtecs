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

			Manager();

			Entity create();

			const std::vector<Entity>& all() const;

			Entity find(const id_t id) const;

			void remove(const id_t id);

			void reset();

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

		Entity(const id_t id);

		inline id_t id() const { return m_id; }		

		bool is_valid() const;
		operator bool() const { return is_valid(); }
		void invalidate();

		void destroy();

		bool operator== (const Entity& other) const;
		bool operator!= (const Entity& other) const;

		template <typename T, typename... P>
		inline T& addComponent(P... args)
		{
			return T{};
		}

		static Entity create();

		static Entity find(const id_t id);

		static std::vector<Entity> all();

		// get the Entity Manager
		static Manager manager();

		// invalid entity definition
		static Entity INVALID;

	private:

		// entity id
		id_t m_id;
		// entity manager
		static Manager s_manager;
	};
}