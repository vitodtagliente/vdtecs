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

		if (!m_unusedIds.empty())
		{
			assigned_id = m_unusedIds.top();
			m_unusedIds.pop();
		}
		else
		{
			assigned_id = ++m_counter;
		}

		m_entities.push_back(Entity{ assigned_id });
		return m_entities.back();
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

	std::vector<Entity::Manager::id_t> Entity::Manager::flush()
	{
		std::vector< Entity::Manager::id_t> deletedEntities;

		for (auto it = m_pendingRemoveEntities.begin(); it != m_pendingRemoveEntities.end(); ++it)
		{
			m_unusedIds.push(it->id());
			deletedEntities.push_back(it->id());

			const auto enIt = std::find_if(
				m_entities.begin(),
				m_entities.end(),
				[id = it->id()](const Entity& entity) { return entity.id() == id; }
			);
			m_entities.erase(enIt);
		}
		m_pendingRemoveEntities.clear();

		return deletedEntities;
	}

	void Entity::Manager::reset()
	{
		m_counter = INVALID_ID;
		m_entities.clear();
		m_unusedIds = std::stack<Entity::id_t>();
		m_pendingRemoveEntities.clear();
	}
}