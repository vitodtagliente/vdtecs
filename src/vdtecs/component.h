/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <cstdint>

namespace ecs
{
	template <typename T>
	class Component
	{
	public:

		using id_t = std::uint32_t;
		using type = T;

		Component()
			: m_id()
		{}

		inline id_t id() const { return m_id; }

		bool operator== (const Component<T>& component) const
		{
			return m_id == component.m_id;
		}
		bool operator!= (const Component<T>& component) const
		{
			return m_id != component.m_id;
		}

	private:

		// component id
		id_t m_id;
	};
}