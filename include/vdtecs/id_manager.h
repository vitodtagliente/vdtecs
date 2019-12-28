/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <cstddef>
#include <algorithm>
#include <map>
#include <stack>
#include <vector>

namespace ecs
{
	class IdManager
	{
	public:

		using id_t = std::uint32_t;

		static constexpr id_t INVALID_ID = 0;
		
		IdManager()
			: m_counter(INVALID_ID)
			, m_unusedIds()
			, m_ids()
			, m_pendingRemoveIds()
		{}

		id_t next()
		{
			id_t assigned_one = INVALID_ID;
			
			if (m_unusedIds.size() > 0)
			{
				assigned_one = m_unusedIds.front();
				m_unusedIds.pop_back(); 
			}
			else
			{
				assigned_one = ++m_counter;
			}

			m_ids.push_back(assigned_one);
			return assigned_one;
		}

		inline const std::vector<id_t>& all() const 
		{ 
			return m_ids; 
		}

		inline const std::vector<id_t>& pendingRemove() const 
		{ 
			return m_pendingRemoveIds; 
		}

		inline id_t find(const id_t id) const
		{
			const auto it = std::find(m_ids.begin(), m_ids.end(), id);
			if (it != m_ids.end())
			{
				return *it;
			}
			return INVALID_ID;
		}

		void remove(const id_t id)
		{
			const auto it = std::find(m_ids.begin(), m_ids.end(), id);
			if (it != m_ids.end())
			{
				m_ids.erase(it);
				m_pendingRemoveIds.push_back(id);
			}
		}

		void clear()
		{
			for (const id_t id : m_pendingRemoveIds)
			{
				m_unusedIds.push_back(id);
			}
			m_pendingRemoveIds.clear();
		}

		void reset()
		{
			m_counter = INVALID_ID;
			m_unusedIds.clear();
			m_ids.clear();
			m_pendingRemoveIds.clear();
		}		

	private:

		// id counter
		id_t m_counter;
		// list of unused ids
		std::vector<id_t> m_unusedIds;
		// list of all active ids
		std::vector<id_t> m_ids;
		// list of ids pending to be removed
		std::vector<id_t> m_pendingRemoveIds;

	};
}