#include "pch.h"
#include "UI.h"
#include "InputManager.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::BeginPlay()
{
}

void UI::Tick()
{
}

void UI::Render(HDC hdc)
{
}

RECT UI::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_pos.x + _size.x / 2,
		_pos.y + _size.y / 2,
	};
	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// 사각형안에 마우스 포인트가 있는지 확인하는 함수
	//return ::PtInRect(&rect, mousePos);

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}
