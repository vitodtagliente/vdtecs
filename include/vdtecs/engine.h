/// Copyright (c) Vito Domenico Tagliente

#pragma once

namespace ecs
{
	class Engine final
	{
	public:

		Engine() = default;

		void update(const float deltaTime);

		static Engine& instance();

	private:

		static Engine s_instance;

	};
}