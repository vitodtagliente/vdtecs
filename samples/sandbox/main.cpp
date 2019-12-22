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
	virtual void each(component_t& position) override
	{
		
	}
};

int main()
{
	Engine engine;
	engine.update(0.1f);

	Entity a = Entity::create();
	Entity b = Entity::create();

	PositionSystem pSystem;
	
	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	return getchar();
}