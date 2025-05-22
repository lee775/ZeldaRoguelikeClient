#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"
#include "Player.h"
#include "UIManager.h"
#include "LineMesh.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

FortressScene::FortressScene()
{
}

FortressScene::~FortressScene()
{
}

void FortressScene::Init()
{
	GET_SINGLE(UIManager)->Init();
	int32 id = 0;
	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::MissileTank);

		player->SetPlayerId(id++);
		player->SetPlayerTurn(true);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 100,400 });
	}

	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::CanonTnak);

		player->SetPlayerId(id++);
		player->SetPlayerTurn(false);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 700,400 });
	}
	ChangePlayerTurn();
}

void FortressScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (auto* object : objects)
		object->Update();

	_sumTime += deltaTime;
	if (_sumTime >= 1.f)
	{
		_sumTime = 0.f;

		int32 time = GET_SINGLE(UIManager)->GetRemainTime();
		// 1�� �������� ���� 0���� ������ 0���� �ض� ��� ��
		time = max(0, time - 1);
		GET_SINGLE(UIManager)->SetRemainTime(time);

		if (time == 0)
			ChangePlayerTurn();
	}
}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLE(UIManager)->Render(hdc);


	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (auto* object : objects)
		object->Render(hdc);
}

void FortressScene::ChangePlayerTurn()
{
	_playerTurn = (_playerTurn + 1) % 2;

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object->GetObjectType() != ObjectType::Player)
			continue;

		Player* player = static_cast<Player*>(object);
		if (player->GetPlayerId() == _playerTurn)
			player->SetPlayerTurn(true);
		else
			player->SetPlayerTurn(false);
	}

	GET_SINGLE(UIManager)->SetRemainTime(10);
	GET_SINGLE(UIManager)->SetStaminaPercent(100.f);
	GET_SINGLE(UIManager)->SetPowerPercent(0.f);
	GET_SINGLE(UIManager)->SetWindPercent(static_cast<float>( - 100 + rand() % 200));
}
