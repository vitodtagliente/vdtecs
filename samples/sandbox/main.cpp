#include <iostream>
#include <string>

#include <vdtecs/ecs.h>

#include "time.h"

using namespace std;
using namespace ecs;

struct Position
{
	int x, y;
};

class PositionSystem : public System<PositionSystem, Position>
{
public:
	virtual void update(const float delta_time) override
	{
		for (Component& component : components())
		{
			component.data().x += 1;
		}
	}
};

struct Character
{
	std::string name;
};

class CharacterSystem : public System<CharacterSystem, Character>
{
public:
	virtual void update(const float delta_time) override
	{
		for (Component& component : components())
		{
			auto entity = Entity::find(component.entity_id());
			if (entity.is_valid())
			{
				auto position = entity.getComponent<PositionSystem::Component>();
				position->data().x += 3;
			}
		}
	}
};

int main()
{
	Engine engine;

	Entity a = Entity::create();
	Entity b = Entity::create();
	// positions
	a.addComponent<PositionSystem::Component>(1, 3);
	b.addComponent<PositionSystem::Component>(2, 5);
	// characters
	a.addComponent<CharacterSystem::Component>("A");
	b.addComponent<CharacterSystem::Component>("B");

	const auto& c = a.getComponent<PositionSystem::Component>();
	const auto& component = a.getComponents<PositionSystem::Component>();

	const auto& f = PositionSystem::instance().getComponentById(2);

	cout << "Entities" << endl;
	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	auto& manager = ISystem::manager();
	manager.add<PositionSystem>();
	manager.add<CharacterSystem>();

	const auto& systems = manager.all();

	// simulate 60 frames
	for (int i = 0; i < 60; ++i)
	{
		engine.update(1.f / 60);
	}

	// positions
	for (auto entity : Entity::all())
	{
		auto position = entity.getComponent<PositionSystem::Component>();
		cout << "Entity " << entity.id() << ", position = x: " << position->data().x << ", y: " << position->data().y << endl;
	}

	return getchar();
}