#pragma once
#include "Creature.h"

class Player;

class GameMonster : public Creature
{
	using Super = Creature;
public:
	GameMonster();
	virtual ~GameMonster() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;

	virtual void OnDamaged(Creature* attacker) override;

protected:
	Flipbook* _flipbookMove[4] = {};
	float _waitSeconds = 0.f;
	//Flipbook* _flipbookAttack[4] = {};

	// TEMP
	Player* _target = nullptr;
};

