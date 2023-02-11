/// Copyright (c) Vito Domenico Tagliente
#pragma once 

#include <cstddef>
#include <map>
#include <vector>

#include "id.h"

namespace ecs
{
	template <typename T>
	class Component final
	{
	public:
		Component() = delete;

		typedef std::tuple<id_t, T> data_t;

		static std::vector<data_t>& data() { return s_data; }
		static std::size_t id() { return s_id; }

		static void clear();
		static void erase(id_t entity_id);
		static T* const find(id_t entity_id);
		static T& push_back(id_t entity_id, const T& data);
		template <typename ...P>
		static T& push_back(id_t entity_id, P... args);

	private:
		static std::vector<data_t> s_data;
		static std::size_t s_id;
		static std::map<id_t, std::size_t> s_lookup;
	};

	template <typename T>
	std::vector<std::tuple<id_t, T>> Component<T>::s_data;
	template <typename T>
	std::size_t Component<T>::s_id = typeid(T).hash_code();
	template <typename T>
	std::map<id_t, std::size_t> Component<T>::s_lookup;

	template<typename T>
	void Component<T>::clear()
	{
		s_data.clear();
		s_entities.clear();
		s_lookup.clear();
	}

	template <typename T>
	void Component<T>::erase(const id_t entity_id)
	{
		const auto& it = s_lookup.find(entity_id);
		if (it != s_lookup.end())
		{
			const std::size_t index = it->second;
			s_lookup.erase(it);
			s_data.erase(s_data.begin() + index);
		}
	}

	template <typename T>
	T* const Component<T>::find(const id_t entity_id)
	{
		const auto& it = s_lookup.find(entity_id);
		if (it != s_lookup.end())
		{
			const std::size_t index = it->second;
			auto& [id, data] = s_data[index];
			return &data;
		}
		return nullptr;
	}

	template <typename T>
	T& Component<T>::push_back(const id_t entity_id, const T& data)
	{
		s_lookup.insert(std::make_pair(entity_id, s_data.size()));
		s_data.push_back(std::make_tuple(entity_id, data));
		return std::get<1>(s_data.back());
	}

	template <typename T>
	template <typename ...P>
	T& Component<T>::push_back(const id_t entity_id, P... args)
	{
		s_lookup.insert(std::make_pair(entity_id, s_data.size()));
		s_data.push_back(std::make_tuple(entity_id, T{ std::forward<P>(args)... }));
		return std::get<1>(s_data.back());
	}
}