#pragma once

// Scene에 배치 할 수 있는 모든 오브젝트를 부르는 말

class Component;
class Collider;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	// 언리얼 방식
	virtual void BeginPlay();
	virtual void Tick();

	virtual void Render(HDC hdc);

	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }

	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	// 유니티에서의 함수명 : OnCellisionEnter2D / OnCollisionExit2D
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* othder);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* othder);

protected:
	Vector _pos = { 0,0 };
	Vector _destPos = { 0,0 };
	LAYER_TYPE _layer = LAYER_OBJECT;
	vector<Component*> _components;
};

