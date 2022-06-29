/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>

#include "isystem.h"

namespace ecs
{
	class Engine final
	{
	public:

		Engine() = default;

		void update(const double delta_time);
		void execute(const std::function<void(ISystem* const)>& handler);

	};
}