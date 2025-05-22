#pragma once

class Collider;

class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);
public:
	void Init(HWND hwnd);
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

private:
	vector<Collider*> _colliders;
};

