#pragma once

#include "FlipbookActor.h"

class Flipbook;
class Collider;
class BoxCollider;

enum class PlayerState
{
	Idle,
	Move,
	Skill,
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player();
	virtual ~Player() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	void SetState(PlayerState state);
	PlayerState GetState() { return _state; }

	void SetDir(Dir dir);
	Dir GetDir() { return _dir; }

	bool CanGo(VectorInt cellPos);

	void SetCellPos(VectorInt cellPos, bool teleport = false);
	VectorInt GetCellPos() { return _cellPos; }

	void UpdateAnimation();

private:
	//void TickInput();
	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickSkill();

private:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

private:
	//Flipbook* _flipbookUp = nullptr;
	//Flipbook* _flipbookDown = nullptr;
	//Flipbook* _flipbookLeft = nullptr;
	//Flipbook* _flipbookRight = nullptr;
	Flipbook* _flipbookIdle[4] = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookAttack[4] = {};

private:
	Vector _speed = {};
	VectorInt _cellPos = {};
	Dir _dir = DIR_DOWN;
	int32 _gravity = 1000;

	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
};

