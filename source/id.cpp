#include <vdtecs/id.h>

#include <chrono>

namespace ecs
{
	id_t id()
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		return static_cast<std::size_t>(now.time_since_epoch().count());
	}
}