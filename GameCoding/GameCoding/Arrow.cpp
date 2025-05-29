#include "pch.h"
#include "Arrow.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "Creature.h"
#include "HitEffect.h"

Arrow::Arrow()
{
	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ArrowUp");
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ArrowDown");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ArrowLeft");
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ArrowRight");
}

Arrow::~Arrow()
{
}

void Arrow::BeginPlay()
{
	Super::BeginPlay();
	UpdateAnimation();
}

void Arrow::Tick()
{
	Super::Tick();

	// TODO
}

void Arrow::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void Arrow::TickIdle()
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	VectorInt nextPos = GetFrontCellPos();
	
	if (CanGo(nextPos))
	{
		SetCellPos(nextPos);
		SetState(MOVE);
	}
	else
	{
		Creature* creature = scene->GetCreatureAt(nextPos);
		if (creature)
		{
			scene->SpawnObject<HitEffect>(nextPos);
			//creature->OnDamaged(_owner);
		}

		scene->RemoveActor(this);
	}
}

void Arrow::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 어느 정도 거리 이상으로 왔으면 도착했다고 인지를 하는 부분
	Vector dir = (_destPos - _pos);
	if (dir.Length() < 5.f)
	{
		SetState(IDLE);
		_pos = _destPos;
	}
	else
	{
		switch (info.dir())
		{
		case DIR_UP:
			_pos.y -= 600 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 600 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 600 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 600 * deltaTime;
			break;
		}
	}
}

void Arrow::UpdateAnimation()
{
	SetFlipbook(_flipbookMove[info.dir()]);
}
