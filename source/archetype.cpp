#include <vdtecs/archetype.h>

namespace ecs
{
	std::vector<Archetype> ArchetypeTable::s_archetypes;
	std::unordered_map<id_t, std::vector<id_t>> ArchetypeTable::s_entities;

	Archetype* const ArchetypeTable::find(const std::unordered_set<id_t>& components)
	{
		const auto& it = std::find_if(
			s_archetypes.begin(),
			s_archetypes.end(),
			[&components](const Archetype& archetype) -> bool
			{
				return archetype.components = components;
			}
		);

		if (it != s_archetypes.end())
		{
			return *it;
		}
		return nullptr;
	}
}