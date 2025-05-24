#pragma once
#include "Creature.h"

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
	//Flipbook* _flipbookAttack[4] = {};
};

