#include <vdtecs/entity.h>
#include <vdtecs/system.h>

namespace ecs
{
	Entity::Entity(const id_t id)
		: m_id(id)
	{ }

	bool Entity::is_valid() const
	{
		return m_id != INVALID_ID;
	}

	void Entity::invalidate()
	{
		m_id = INVALID_ID;
	}

	void Entity::destroy()
	{
		if (is_valid())
		{
			s_manager.remove(m_id);
			m_id = INVALID_ID;
		}
	}

	bool Entity::operator== (const Entity& other) const
	{
		return m_id == other.m_id;
	}

	bool Entity::operator!= (const Entity& other) const
	{
		return m_id != other.m_id;
	}

	Entity Entity::create()
	{
		return s_manager.create();
	}

	Entity Entity::find(const id_t id)
	{
		return s_manager.find(id);
	}

	const std::vector<Entity>& Entity::all()
	{
		return s_manager.all();
	}

	// get the Entity Manager
	Entity::Manager& Entity::manager()
	{
		return s_manager;
	}

	// Invalid Entity
	Entity Entity::INVALID{ INVALID_ID };
	// Entity Manager
	Entity::Manager Entity::s_manager{};
}