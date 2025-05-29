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

	SetState(MOVE);
	SetState(IDLE);
}

void MainGameObject::Tick()
{
	Super::Tick();

	// TODO
	switch (info.state())
	{
	case IDLE:
		TickIdle();
		break;
	case MOVE:
		TickMove();
		break;
	case SKILL:
		TickSkill();
		break;
	}

	//TickGravity();
}

void MainGameObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

VectorInt MainGameObject::GetCellPos()
{
	return VectorInt{info.posx(), info.posy() };
}

void MainGameObject::SetState(ObjectState state)
{
	if (info.state() == state)
		return;

	info.set_state(state);
	UpdateAnimation();
}

void MainGameObject::SetDir(Dir dir)
{
	info.set_dir(dir);
	UpdateAnimation();
}

bool MainGameObject::CanGo(VectorInt cellPos)
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

Dir MainGameObject::GetLookAtDir(VectorInt cellPos)
{
	VectorInt dir = cellPos - GetCellPos();
	if (dir.x > 0)
		return DIR_RIGHT;
	else if (dir.x < 0)
		return DIR_LEFT;
	else if (dir.y > 0)
		return DIR_UP;
	else
		return DIR_DOWN;
}

void MainGameObject::SetCellPos(VectorInt cellPos, bool teleport)
{
	info.set_posx(cellPos.x);
	info.set_posy(cellPos.y);

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;
}

VectorInt MainGameObject::GetFrontCellPos()
{
	switch (info.dir())
	{
	case DIR_UP:
		return GetCellPos() + VectorInt{0,-1};
	case DIR_DOWN:
		return GetCellPos() + VectorInt{ 0,1 };
	case DIR_LEFT:
		return GetCellPos() + VectorInt{ -1,0 };
	case DIR_RIGHT:
		return GetCellPos() + VectorInt{ 1,0 };
	}

	return GetCellPos();
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
