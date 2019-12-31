#include <vdtecs/engine.h>
#include <vdtecs/system_manager.h>

namespace ecs
{
	// singleton instance 
	Engine Engine::s_instance{};

	Engine& Engine::instance()
	{
		return s_instance;
	}

	void Engine::update(const float delta_time)
	{
		for (ISystem* const system : SystemManager::instance())
		{
			system->update(delta_time);
		}
	}
}