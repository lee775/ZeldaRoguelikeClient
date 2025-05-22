#include "pch.h"
#include "MainGameObject.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "DevScene.h"
#include "SceneManager.h"

MainGameObject::MainGameObject()
{

}

MainGameObject::~MainGameObject()
{
}

void MainGameObject::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);
}

void MainGameObject::Tick()
{
	Super::Tick();

	// TODO
	switch (_state)
	{
	case ObjectState::Idle:
		TickIdle();
		break;
	case ObjectState::Move:
		TickMove();
		break;
	case ObjectState::Skill:
		TickSkill();
		break;
	}

	//TickGravity();
}

void MainGameObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

void MainGameObject::SetState(ObjectState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void MainGameObject::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}

bool MainGameObject::CanGo(VectorInt cellPos)
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

void MainGameObject::SetCellPos(VectorInt cellPos, bool teleport)
{
	_cellPos = cellPos;

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;
}

void MainGameObject::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vector pos = GetPos();

	RECT intersect = {};
	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;
		if (w >= h)
		{
			if (intersect.top == r2.top)
			{
				pos.y -= h;
			}
			else
			{
				pos.y += h;
			}
		}
		else
		{
			if (intersect.left == r2.left)
			{
				pos.x -= w;
			}
			else
			{
				pos.x += w;
			}
		}
	}
	SetPos(pos);
}
