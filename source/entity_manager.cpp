#include <vdtecs/entity.h>

namespace ecs
{
	Entity::Manager::Manager()
		: m_counter(INVALID_ID)
		, m_entities()
		, m_pendingRemoveEntities()
		, m_unusedIds()
	{}

	Entity Entity::Manager::create()
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

	const std::vector<Entity>& Entity::Manager::all() const
	{
		return m_entities;
	}

	Entity Entity::Manager::find(const id_t id) const
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

	void Entity::Manager::remove(const id_t id)
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

	void Entity::Manager::flush()
	{
		for (auto it = m_pendingRemoveEntities.begin(); it != m_pendingRemoveEntities.end(); ++it)
		{
			m_unusedIds.push_back(it->id());
			m_pendingRemoveEntities.erase(it);
		}
	}

	void Entity::Manager::reset()
	{
		m_counter = INVALID_ID;
		m_entities.clear();
		m_unusedIds.clear();
		m_pendingRemoveEntities.clear();
	}
}