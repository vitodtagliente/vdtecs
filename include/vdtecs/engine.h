/// Copyright (c) Vito Domenico Tagliente

#pragma once

namespace ecs
{
	class Engine final
	{
	public:

		Engine() = default;

		void update(const float delta_time);

	};
}