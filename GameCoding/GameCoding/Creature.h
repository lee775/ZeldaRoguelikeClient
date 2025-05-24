#pragma once
#include "MainGameObject.h"

class Creature : public MainGameObject
{
	using Super = MainGameObject;
public:
	Creature();
	virtual ~Creature() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;

public:
	virtual void OnDamaged(Creature* attacker);

	void SetStat(Stat stat) { _status = stat; }
	Stat& GetStat() { return _status; }

protected:
	Stat _status;
};

