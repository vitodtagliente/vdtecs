#include <vdtecs/engine.h>
#include <vdtecs/isystem.h>

namespace ecs
{
	void Engine::update(const float delta_time)
	{
		// update all systems
		for (ISystem* const system : ISystem::manager())
		{
			system->update(delta_time);
		}
		// flush pending data
		Entity::manager().flush();
	}
}