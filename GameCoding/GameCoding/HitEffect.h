#pragma once
#include "MainGameObject.h"

class HitEffect : public MainGameObject
{
	using Super = MainGameObject;
public:
	HitEffect();
	virtual ~HitEffect() override;

	// 언리얼 방식
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void UpdateAnimation() override;
};

