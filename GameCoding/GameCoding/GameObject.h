#pragma once

class Component;


// 언리얼로 치면 Actor임
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	// 언리얼 방식
	virtual void Start();
	virtual void Update();

	virtual void Render(HDC hdc);

	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }

	void AddComponent(Component* component);

protected:
	Vector _pos = { 0,0 };
	vector<Component*> _components;
};

