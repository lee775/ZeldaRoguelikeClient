#pragma once
#include "Projectile.h"

class Arrow : public Projectile
{
	using Super = Projectile;
public:
	Arrow();
	virtual ~Arrow() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;
};

