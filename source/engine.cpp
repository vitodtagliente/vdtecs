#include <vdtecs/engine.h>

namespace ecs
{
	void Engine::update(const double delta_time)
	{
		// update all systems
		for (ISystem* const system : ISystem::manager())
		{
			system->update(delta_time);
		}

		// flush pending data
		const auto& deletedEntities = Entity::manager().flush();
		if (!deletedEntities.empty())
		{
			for (ISystem* const system : ISystem::manager())
			{
				system->removeEntities(deletedEntities);
			}
		}
	}

	void Engine::execute(const std::function<void(ISystem* const)>& handler)
	{
		for (ISystem* const system : ISystem::manager())
		{
			handler(system);
		}
	}
}