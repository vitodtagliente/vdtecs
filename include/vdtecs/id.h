/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cstddef>

namespace ecs
{
	typedef std::size_t id_t;
	constexpr id_t INVALID_ID = 0;

	id_t id();
}