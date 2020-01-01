#include <vdtecs/system_manager.h>

namespace ecs
{
	// instance initialization
	SystemManager SystemManager::s_instance{};

	void SystemManager::add(ISystem* const system)
	{
		system->init();
		m_systems.push_back(system);
	}

	SystemManager::const_iterator SystemManager::begin() const noexcept
	{
		return m_systems.begin();
	}

	SystemManager::const_iterator SystemManager::end() const noexcept
	{
		return m_systems.end();
	}

	const std::vector<ISystem*>& SystemManager::all() const 
	{ 
		return m_systems; 
	}

	SystemManager& SystemManager::instance()
	{
		return s_instance;
	}
}