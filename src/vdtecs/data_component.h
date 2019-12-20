/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include "type_id.h"

namespace ECS
{
	template <typename T>
	class DataComponent
	{
		using id_t = size_t;
		using type = T;

		DataComponent()
			: m_id()
			, m_data()
		{}

		DataComponent(const size_t id, const T& data)
			: m_id(id)
			, m_data(data)
		{}

		inline id_t id() const { return m_id; }
		inline const T& data() const { return m_data; }

		bool operator== (const DataComponent<T>& other) const
		{
			return m_id == other.m_id;
		}
		bool operator!= (const DataComponent<T>& other) const
		{
			return m_id != other.m_id;
		}
		
	private:

		id_t m_id;
		T m_data;
	};
}