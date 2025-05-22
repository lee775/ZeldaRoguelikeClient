#pragma once

class Component;


// �𸮾�� ġ�� Actor��
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	// �𸮾� ���
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

