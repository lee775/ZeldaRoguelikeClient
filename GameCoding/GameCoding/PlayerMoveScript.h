#pragma once
#include "Component.h"

class PlayerMoveScript : public Component
{
public:
	PlayerMoveScript();
	virtual ~PlayerMoveScript();
	virtual void BeginPlay() {}
	virtual void TickComponent() {}
	virtual void Render(HDC hdc) {}

};

