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

	void GameOver() { _isDead = true; }
	bool getIsDead() { return _isDead; }

private:
	void TickInput();
	void TryMove();

	//void TickInput();
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;

	void SyncToServer();

private:
	bool _keyPressed = false;
	bool _isDead = false;
};

