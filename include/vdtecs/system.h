/// Copyright (c) Vito Domenico Tagliente

#pragma once 

#include <cstddef>
#include <memory>
#include <vector>

#include "id.h"

namespace ecs
{
	struct ISystem
	{
		virtual ~ISystem() = default;
		virtual void run() = 0;
	};

	class SystemRegistry final
	{
	public:
		void push_back(std::unique_ptr<ISystem> system);
		template <typename T, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
		void push_back()
		{
			m_systems.push_back(std::unique_ptr<ISystem>(new T()));
		}
		template <typename T, typename...A, typename TEnabled = std::enable_if<std::is_base_of<ISystem, T>::value>>
		void push_back(A... args)
		{
			m_systems.push_back(std::unique_ptr<ISystem>(new T(...args)));
		}

		void run();

		const std::vector<std::unique_ptr<ISystem>>& systems() const { return m_systems; }

	private:
		std::vector<std::unique_ptr<ISystem>> m_systems;
	};

	template <typename C>
	class System : public ISystem
	{
	public:
		System() = default;
		virtual ~System() = default;

		virtual void run() final;

	protected:
		virtual void process(std::vector<std::pair<id_t, C>>& components) = 0;

	private:
		static std::size_t s_id;
	};

	template <typename C>
	std::size_t System<C>::s_id = typeid(T).hash_code();
	template <typename C>
	void System<C>::run()
	{
		process(Component<C>::data());
	}
}