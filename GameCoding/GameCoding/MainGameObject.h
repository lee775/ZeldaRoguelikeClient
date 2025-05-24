#pragma once
#include "FlipbookActor.h"

class Flipbook;
class Collider;
class BoxCollider;

class MainGameObject : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	MainGameObject();
	virtual ~MainGameObject() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	ObjectState GetState() { return _state; }
	Dir GetDir() { return _dir; }
	VectorInt GetCellPos() { return _cellPos; }

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickSkill() {};
	virtual void UpdateAnimation() {};

public:
	void SetState(ObjectState state);
	void SetDir(Dir dir);

	bool CanGo(VectorInt cellPos);
	void SetCellPos(VectorInt cellPos, bool teleport = false);
	VectorInt GetFrontCellPos();


private:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

protected:
	Vector _speed = {};
	VectorInt _cellPos = {};
	Dir _dir = DIR_DOWN;
	ObjectState _state = ObjectState::Idle;
};

