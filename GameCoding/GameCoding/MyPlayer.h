#pragma once

#include "Player.h"

class MyPlayer : public Player
{
	using Super = Player;
public:
	MyPlayer();
	virtual ~MyPlayer() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	void TickInput();
	void TryMove();

	//void TickInput();
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;

private:
	bool _keyPressed = false;
};

