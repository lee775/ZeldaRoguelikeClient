#pragma once
#include "Component.h"

class Sprite;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(Sprite* sprite) { _sprite = sprite; }
private:
	Sprite* _sprite = nullptr;
};

