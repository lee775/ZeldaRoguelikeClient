#include "pch.h"
#include "GameMonster.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "DevScene.h"
#include "SceneManager.h"

GameMonster::GameMonster()
{
	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeUp");
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeDown");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeLeft");
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeRight");
}

GameMonster::~GameMonster()
{
}

void GameMonster::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);
}

void GameMonster::Tick()
{
	Super::Tick();

	// TODO
}

void GameMonster::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void GameMonster::TickIdle()
{
}

void GameMonster::TickMove()
{
}

void GameMonster::TickSkill()
{
}

void GameMonster::UpdateAnimation()
{
	SetFlipbook(_flipbookMove[_dir]);
}
