#include <iostream>
#include <string>

#include <vdtecs/ecs.h>

using namespace std;
using namespace ecs;

struct vector3
{
	float x = 0.f, y = 0.f, z = 0.f;
};

struct Transform
{
	vector3 position;
};

struct Character
{
	std::string name;
};

class PositionSystem : public System<Transform>
{
protected:
	virtual void process(std::vector<std::pair<id_t, Transform>>& transforms) override
	{
		for (auto& [entity_id, transform] : transforms)
		{
			transform.position.x += 1.0f;
		}
	}
};

int main()
{
	SystemRegistry registry;

	Entity a = Entity::create();
	Entity b = Entity::create();

	// positions
	a.addComponent<Transform>();
	b.addComponent<Transform>();
	// characters
	a.addComponent<Character>("Entity A");
	b.addComponent<Character>("Entity B");

	cout << Component<Transform>::id() << endl;
	for (const auto& [entity_id, transform] : Component<Transform>::data())
	{
		cout << "entity_id: " << entity_id << ", x: " << transform.position.x << ", y: " << transform.position.y << endl;
	}
	cout << (Component<Transform>::find(a) != nullptr) << endl;
	Component<Transform>::erase(a);
	cout << (Component<Transform>::find(a) != nullptr) << endl;

	registry.push_back<PositionSystem>();
	for (int i = 0; i < 100; ++i)
	{
		registry.run();
	}

	for (const auto& [entity_id, transform] : Component<Transform>::data())
	{
		cout << "entity_id: " << entity_id << ", x: " << transform.position.x << ", y: " << transform.position.y << endl;
	}

	return getchar();
}