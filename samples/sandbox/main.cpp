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
	a.addComponent<PositionSystem::Component>(1, 3);
	a.addComponent<PositionSystem::Component>(2, 5);
	a.addComponent<PositionSystem::Component>(3, 3);
	
	const auto& c = a.getComponent<PositionSystem::Component>();
	const auto& component = a.getComponents<PositionSystem::Component>();
	
	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	return getchar();
}