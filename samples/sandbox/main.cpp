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
	int level = 0;
};

class PositionSystem : public System<Transform>
{
protected:
	virtual void process(id_t, Transform& transform) override
	{
		transform.position.x += 1.0f;
	}
};

class FooSystem : public System<Character, Transform>
{
protected:
	virtual void process(id_t, Character& character, Transform&) override
	{
		character.level++;
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
	cout << (Component<Transform>::find(b) != nullptr ? "B found!" : "B not found") << endl;
	Component<Transform>::erase(b);
	cout << (Component<Transform>::find(b) != nullptr ? "B found!" : "B not found") << endl;

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