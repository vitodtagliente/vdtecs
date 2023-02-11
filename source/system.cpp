#include <vdtecs/system.h>

namespace ecs
{
	void SystemRegistry::push_back(std::unique_ptr<ISystem> system)
	{
		m_systems.push_back(std::move(system));
	}

	void SystemRegistry::run()
	{
		for (const auto& system : m_systems)
		{
			system->run();
		}
	}
}