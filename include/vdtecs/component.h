/// Copyright (c) Vito Domenico Tagliente
#pragma once 

#include <cstddef>
#include <map>
#include <vector>

#include "id.h"

namespace ecs
{
	class ComponentTable final
	{
	public:

		template <typename ...C>
		struct iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using index_t = std::map<id_t, std::vector<std::pair<id_t, std::size_t>>>::iterator;
			using value_t = std::tuple<C*...>;

			iterator(index_t ptr) : m_ptr(ptr) { }

			value_t& operator*() { return m_value; }
			value_t* operator->() { return &m_value; }
			iterator& operator++()
			{
				m_ptr++;
				update();
				return *this;
			}
			id_t entity() const { return m_ptr->first; }
			operator bool() const { return m_valid; }
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
			friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };

		private:
			void update()
			{
				static const auto& find_address = [](const id_t component_id, const std::vector<std::pair<id_t, std::size_t>>& list, bool& success) -> std::size_t
				{
					const auto& it = std::find_if(
						list.begin(),
						list.end(),
						[component_id](const std::pair<id_t, std::size_t>& pair) -> bool
						{
							return pair.first == component_id;
						}
					);

					if (it != list.end())
					{
						return success = true, it->second;
					}
					return success = false, 0;
				};

				m_valid = true;
				const std::vector<std::pair<id_t, std::size_t>>& list = m_ptr->second;
				m_value = std::make_tuple(reinterpret_cast<C*>(find_address(Component<C>::id(), list, m_valid))...);
			}

			index_t m_ptr;
			bool m_valid{ false };
			value_t m_value;
		};

		static void clear();
		static void erase(id_t entity_id);
		static void erase(id_t entity_id, id_t component_id);
		static void push_back(id_t entity_id, id_t component_id, std::size_t data_address);

		template <typename ...C>
		static iterator<C...> begin() { return iterator<C...>(s_data.begin()); }
		template <typename ...C>
		static iterator<C...> end() { return iterator<C...>(s_data.end()); }

	private:
		static std::map<id_t, std::vector<std::pair<id_t, std::size_t>>> s_data;
	};

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
		static T* const get(std::size_t address);
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
			ComponentTable::erase(entity_id, s_id);
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
	T* const Component<T>::get(const std::size_t address)
	{
		return reinterpret_cast<T*>(address);
	}

	template <typename T>
	T& Component<T>::push_back(const id_t entity_id, const T& data)
	{
		s_lookup.insert(std::make_pair(entity_id, s_data.size()));
		s_data.push_back(std::make_tuple(entity_id, data));
		T& component = std::get<1>(s_data.back());
		ComponentTable::push_back(entity_id, s_id, reinterpret_cast<std::size_t>(&component));
		return component;
	}

	template <typename T>
	template <typename ...P>
	T& Component<T>::push_back(const id_t entity_id, P... args)
	{
		s_lookup.insert(std::make_pair(entity_id, s_data.size()));
		s_data.push_back(std::make_tuple(entity_id, T{ std::forward<P>(args)... }));
		T& component = std::get<1>(s_data.back());
		ComponentTable::push_back(entity_id, s_id, reinterpret_cast<std::size_t>(&component));
		return component;
	}
}