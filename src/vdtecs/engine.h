#pragma once

#include "entity.h"
#include "type_id.h"

namespace ecs
{
	class Engine final
	{
	public:

		Engine()
		{ }

		void update(const float deltaTime)
		{
			// m_systemManager.update(deltaTime);
		}

		template <typename T, typename... P>
		void addSystem(P... t_args)
		{
			m_systemManager.add<T>(std::forward<P>(t_args)...);
		}

	private:

	};
}