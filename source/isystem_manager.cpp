#include <vdtecs/isystem.h>

namespace ecs
{
	void ISystem::Manager::add(ISystem* const system)
	{
		system->init();
		m_systems.push_back(system);
	}

	ISystem::Manager::const_iterator ISystem::Manager::begin() const noexcept
	{
		return m_systems.begin();
	}

	ISystem::Manager::const_iterator ISystem::Manager::end() const noexcept
	{
		return m_systems.end();
	}

	const std::vector<ISystem*>& ISystem::Manager::all() const
	{
		return m_systems;
	}
}