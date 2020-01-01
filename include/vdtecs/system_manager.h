/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <algorithm>
#include <memory>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include "system.h"

namespace ecs
{
	class SystemManager final
	{
	public:

		using iterator = std::vector<ISystem*>::iterator;
		using const_iterator = std::vector<ISystem*>::const_iterator;

		// register a system
		template <typename T, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
		void add()
		{
			add(&T::instance());
		}

		void add(ISystem* const system);

		template <typename T, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
		T* const get() const
		{
			for (ISystem* const system : m_systems)
			{
				T* const t_system = static_cast<T*>(system);
				if (t_system != nullptr)
					return t_system;
			}
			return nullptr;
		}

		template <typename T, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
		void remove()
		{
			const auto it = std::find_if(
				m_systems.begin(),
				m_systems.end(),
				[](ISystem* const system)
				{
					return static_cast<T*>(system) != nullptr;
				}
			);

			if (it != m_systems.end())
			{
				(*it)->uninit();
				m_systems.erase(it);
			}
		}

		// retrieve the systems vector
		const std::vector<ISystem*>& all() const;

		// iterators
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;

		static SystemManager& instance();

	private:

		SystemManager() = default;
		~SystemManager() = default;

		// systems collection
		std::vector<ISystem*> m_systems;
		// singleton
		static SystemManager s_instance;
	};
}