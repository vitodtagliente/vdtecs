#include <iostream>
#include <vdtecs/ecs.h>

using namespace std;
using namespace ecs;

int main()
{
	Engine engine;
	engine.update(0.1f);

	Entity a = Entity::create();
	Entity b = Entity::create();

	for (auto entity : Entity::all())
	{
		cout << entity.id() << endl;
	}

	return getchar();
}