#include <vdtecs/archetype.h>

namespace ecs
{
	std::vector<Archetype> ArchetypeTable::s_archetypes;
	std::unordered_map<id_t, std::vector<id_t>> ArchetypeTable::s_entities;
}