#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "DevScene.h"
#include "SceneManager.h"

Player::Player()
{
	//{
	//	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
	//	Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFilpbook(L"FB_MoveUp");
	//	fb->SetInfo({ texture, L"FB_MoveUp",{200,200},0,9,1,0.5f });
	//}
	_flipbookIdle[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleUp");
	_flipbookIdle[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleDown");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleLeft");
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleRight");

	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveUp");
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveDown");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft");
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight");

	_flipbookAttack[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackUp");
	_flipbookAttack[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackDown");
	_flipbookAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackLeft");
	_flipbookAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackRight");

	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	SetState(PlayerState::Move);
	SetState(PlayerState::Idle);

	SetCellPos({ 5,5 }, true);
}

void Player::Tick()
{
	Super::Tick();

	// TODO
	switch (_state)
	{
	case PlayerState::Idle:
		TickIdle();
		break;
	case PlayerState::Move:
		TickMove();
		break;
	case PlayerState::Skill:
		TickSkill();
		break;
	}

	//TickGravity();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	if (b1 == nullptr || b2 == nullptr)
		return;

	AdjustCollisionPos(b1, b2);

	if (b2->GetCollisionLayerType() == CLT_GROUND)
	{
		SetState(PlayerState::Move);
	}
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);
	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayerType() == CLT_GROUND)
	{

	}

}

void Player::SetState(PlayerState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void Player::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}

bool Player::CanGo(VectorInt cellPos)
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if(scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

void Player::SetCellPos(VectorInt cellPos, bool teleport)
{
	_cellPos = cellPos;

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case PlayerState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookMove[_dir]);
		else
			SetFlipbook(_flipbookIdle[_dir]);
		break;
	case PlayerState::Move:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	case PlayerState::Skill:
		SetFlipbook(_flipbookAttack[_dir]);
		break;
	}
}

//void Player::TickInput()
//{
//	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
//
//	// 로직
//	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
//	{
//		_pos.y -= 200 * deltaTime;
//		SetFlipbook(_flipbookUp);
//	}
//	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
//	{
//		_pos.y += 200 * deltaTime;
//		SetFlipbook(_flipbookDown);
//	}
//	else if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
//	{
//		_pos.x -= 200 * deltaTime;
//		SetFlipbook(_flipbookLeft);
//	}
//	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
//	{
//		_pos.x += 200 * deltaTime;
//		SetFlipbook(_flipbookRight);
//	}
//}

void Player::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_keyPressed = true;
	// 1칸 단위로 움직일수 있게함
	VectorInt deltaXY[4] = { {0,-1},{0,1},{-1,0},{1,0} };

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		SetDir(DIR_UP);

		VectorInt nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(PlayerState::Move);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetDir(DIR_DOWN);

		VectorInt nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(PlayerState::Move);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);

		VectorInt nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(PlayerState::Move);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);

		VectorInt nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(PlayerState::Move);
		}
	}
	else
	{
		_keyPressed = false;
		if (_state == PlayerState::Idle)
			UpdateAnimation();
	}
}

void Player::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	Vector dir = (_destPos - _pos);
	if (dir.Length() < 10.f)
	{
		SetState(PlayerState::Idle);
		_pos = _destPos;
	}
	else
	{
		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= 200 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 200 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 200 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 200 * deltaTime;
			break;
		}
	}
}

void Player::TickSkill()
{
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
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
