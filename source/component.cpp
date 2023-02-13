#include <vdtecs/component.h>

namespace ecs
{
	std::map<id_t, std::vector<std::pair<id_t, std::size_t>>> ComponentTable::s_data;

	void ComponentTable::clear()
	{
		s_data.clear();
	}

	void ComponentTable::erase(const id_t entity_id)
	{
		s_data.erase(entity_id);
	}

	void ComponentTable::erase(const id_t entity_id, const id_t component_id)
	{
		const auto& it = s_data.find(entity_id);
		if (it == s_data.end()) return;

		std::vector<std::pair<id_t, std::size_t>>& list = it->second;
		const auto& comp_it = std::find_if(
			list.begin(),
			list.end(),
			[component_id](const std::pair<id_t, std::size_t>& pair) -> bool
			{
				return pair.first == component_id;
			}
		);
		list.erase(comp_it);
	}

	void ComponentTable::push_back(const id_t entity_id, const id_t component_id, std::size_t data_address)
	{
		const auto& it = s_data.find(entity_id);
		if (it == s_data.end())
		{
			std::vector<std::pair<id_t, std::size_t>> list;
			list.push_back(std::make_pair(component_id, data_address));
			s_data.insert(std::make_pair(entity_id, list));
		}
		else
		{
			std::vector<std::pair<id_t, std::size_t>>& list = it->second;
			list.push_back(std::make_pair(component_id, data_address));
		}
	}
}