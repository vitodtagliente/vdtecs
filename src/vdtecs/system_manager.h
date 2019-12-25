/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>
#include "system.h"
#include "type_id.h"

namespace ecs
{
	class SystemManager final
	{
	public:

		using iterator = std::vector<ISystem*>::iterator;
		using const_iterator = std::vector<ISystem*>::const_iterator;

		template <typename T, typename... P>
		ISystem* const add(P... args)
		{
			ISystem* const system = new T(std::forward<P>(args)...);
			system->init();
			m_systems.push_back(system);
			return system;
		}

		template <typename T>
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

		template <typename T>
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

		const_iterator begin() const noexcept
		{ 
			return m_systems.begin(); 
		}

		const_iterator end() const noexcept
		{
			return m_systems.end();
		}

		static SystemManager& instance()
		{
			return s_instance;
		}

	private:

		SystemManager()
		{}

		~SystemManager() = default;

		// systems collection
		std::vector<ISystem*> m_systems;
		// singleton
		static SystemManager s_instance;
	};

	// instance initialization
	SystemManager SystemManager::s_instance{};
}