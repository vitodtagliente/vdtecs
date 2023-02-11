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
	virtual void process(std::vector<std::pair<id_t, Transform>>& data) override
	{
		for (auto& [entity_id, transform] : data)
		{
			transform.position.x += 1.0f;
		}
	}
};

// class FooSystem : public System<Character, Transform>
// {
// protected:
// 	virtual void process(std::vector<std::pair<id_t, Character, Transform>>& data) override
// 	{
// 		for (auto& [entity_id, character, transform] : data)
// 		{
// 			character.level++;
// 		}
// 	}
// };

int main()
{
	SystemRegistry registry;

	Entity a = Entity::create();
	Entity b = Entity::create();

	ComponentIterator<Transform, Character> it;
	Transform& t = it.get<0, Transform>();
	t.position.x = 9;

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
	cout << (Component<Transform>::find(a) != nullptr ? "A found!" : "A not found") << endl;
	Component<Transform>::erase(a);
	cout << (Component<Transform>::find(a) != nullptr ? "A found!" : "A not found") << endl;

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