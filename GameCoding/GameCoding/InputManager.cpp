#include "pch.h"
#include "InputManager.h"

InputManager* InputManager::s_instance = nullptr;

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	// 키 하나가 눌려있는지 확인하는것
	//::GetAsyncKeyState();
	
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	// 현재 키보드 전체의 상태를 전부 가져오는것
	if (::GetKeyboardState(asciiKeys) == false)
		return;
	
	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려 있으면 true
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 이미 누른 상태라면 PRESS
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		else
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 이미 누른 상태라면 PRESS
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	// 창 위의 Mouse좌표 알아오기
	::GetCursorPos(&_mousePos); // 커서의 좌표를 알아온다
	::ScreenToClient(_hwnd, &_mousePos);
}
