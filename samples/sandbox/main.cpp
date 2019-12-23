#include <iostream>
#include <vdtecs/ecs.h>

using namespace std;
using namespace ecs;

struct Position : public Component<Position>
{
	int x;
	int y;
};

class PositionSystem : public System<Position>
{
private:
	virtual void each(Position& position, const float delta_time) override
	{
		
	}
};

int main()
{
	Engine engine;
	engine.update(0.1f);

	Entity a = Entity::create();
	Entity b = Entity::create();

	SystemManager manager;
	manager.add<PositionSystem>();
	PositionSystem* const system = manager.get<PositionSystem>();
	manager.remove<PositionSystem>();

	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	return getchar();
}