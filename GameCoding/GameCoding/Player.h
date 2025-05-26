#pragma once

#include "Creature.h"

class Flipbook;
class Collider;
class BoxCollider;

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) override;
private:
	//void TickInput();
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;

	void SetWeaponType(WeaponType weaponType) { _weaponType = weaponType; }
	WeaponType GetWeaponType() { return _weaponType; }


private:
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);

private:
	Flipbook* _flipbookIdle[4] = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookAttack[4] = {};
	Flipbook* _flipbookBow[4] = {};
	Flipbook* _flipbookStaff[4] = {};

	bool _keyPressed = false;
	WeaponType _weaponType = WeaponType::Sword;
};

