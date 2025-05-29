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
#include "Player.h"
#include "HitEffect.h"

GameMonster::GameMonster()
{
	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeUp");
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeDown");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeLeft");
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeRight");

	_status.hp = 50;
	_status.maxHp = 50;
	_status.attack = 10;
	_status.defence = 0;
}

GameMonster::~GameMonster()
{
}

void GameMonster::BeginPlay()
{
	Super::BeginPlay();

	SetState(MOVE);
	SetState(IDLE);
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
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	// Find Player
	if (_target == nullptr)
		_target = scene->FindClosestPlayer(GetCellPos());

	if (_target)
	{
		VectorInt dir = _target->GetCellPos() - GetCellPos();
		int32 dist = abs(dir.x) + abs(dir.y);
		if (dist == 1)
		{
			// 공격
			SetDir(GetLookAtDir(_target->GetCellPos()));
			SetState(SKILL);
			_waitSeconds = 0.5f; // 공격 종료 시간
		}
		else
		{
			vector<VectorInt> path;
			if (scene->FindPath(GetCellPos(), _target->GetCellPos(), OUT path))
			{
				if (path.size() > 1)
				{
					VectorInt nextPos = path[1];
					if (scene->CanGo(nextPos))
					{
						SetCellPos(nextPos);
						SetState(MOVE);
					}
				}
				else
					SetCellPos(path[0]);
			}
		}
	}
}

void GameMonster::TickMove()
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
		bool horizontal = abs(dir.x) > abs(dir.y);
		if (horizontal)
			SetDir(dir.x < 0 ? DIR_LEFT : DIR_RIGHT);
		else
			SetDir(dir.y < 0 ? DIR_UP : DIR_DOWN);

		switch (info.dir())
		{
		case DIR_UP:
			_pos.y -= 50 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 50 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 50 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 50 * deltaTime;
			break;
		}
	}
}

void GameMonster::TickSkill()
{
	if (_flipbook == nullptr)
		return;

	if (_waitSeconds > 0)
	{
		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
		_waitSeconds = max(0, static_cast<int32>(_waitSeconds - deltaTime));
		return;
	}

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	Creature* creature = scene->GetCreatureAt(GetFrontCellPos());
	if (creature)
	{
		scene->SpawnObject<HitEffect>(GetFrontCellPos());
		creature->OnDamaged(this);
	}

	SetState(IDLE);
}

void GameMonster::UpdateAnimation()
{
	SetFlipbook(_flipbookMove[info.dir()]);
}

void GameMonster::OnDamaged(Creature* attacker)
{
	Super::OnDamaged(attacker);

	if (info.state() == IDLE)
	{

	}
}
