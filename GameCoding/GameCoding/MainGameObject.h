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

	ObjectState GetState() { return info.state(); }
	Dir GetDir() { return info.dir(); }
	VectorInt GetCellPos();
	int64 GetObjectId() { return info.objectid(); }
	void SetObjectId(int64 id) { info.set_objectid(id); }
	void SpawnHitEffect();

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickSkill() {};
	virtual void UpdateAnimation() {};

public:
	void SetState(ObjectState state);
	void SetDir(Dir dir);

	bool CanGo(VectorInt cellPos);
	Dir GetLookAtDir(VectorInt cellPos);

	void SetCellPos(VectorInt cellPos, bool teleport = false);
	VectorInt GetFrontCellPos();


private:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

protected:
	bool _dirtyFlag = false;

public:
	Protocol::ObjectInfo info;
};

