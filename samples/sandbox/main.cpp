#include <iostream>
#include <vdtecs/ecs.h>

using namespace std;
using namespace ecs;

struct Position
{
	int x, y;
};

class PositionSystem : public System<PositionSystem, Position>
{
public:

};

int main()
{
	Engine engine;
	engine.update(0.1f);

	Entity a = Entity::create();
	Entity b = Entity::create();
	a.addComponent<Position>(1, 3);
	
	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	PositionSystem::instance().addComponent(a);

	return getchar();
}