#include <iostream>
#include <vdtecs/ecs.h>

#include "stress.h"
#include "time.h"
#include "timer.h"

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

int main()
{
	Time time;

	Engine engine;
	engine.update(0.1f);

	Entity a = Entity::create();
	Entity b = Entity::create();
	a.addComponent<PositionSystem::Component>(1, 3);
	a.addComponent<PositionSystem::Component>(2, 5);
	a.addComponent<PositionSystem::Component>(3, 3);
	
	const auto& c = a.getComponent<PositionSystem::Component>();
	const auto& component = a.getComponents<PositionSystem::Component>();
	
	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	auto& manager = SystemManager::instance();
	manager.add<PositionSystem>();

	const auto& systems = SystemManager::instance().all();

	// performance stress

	constexpr int num_cycles = 10;
	for (int i = 0; i < num_cycles; ++i)
	{
		time.tick();
	}

	return getchar();
}