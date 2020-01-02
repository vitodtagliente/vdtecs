#include <vdtecs/isystem.h>

namespace ecs
{
	ISystem::Manager ISystem::s_instance {};

	ISystem::Manager& ISystem::manager()
	{
		return s_instance;
	}
}