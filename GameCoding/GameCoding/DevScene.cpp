#include "pch.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "PlayerMoveScript.h"
#include "Flipbook.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Button.h"
#include "TestPanel.h"
#include "TileMapActor.h"
#include "TileMap.h"
#include "SoundManager.h"
#include "Sound.h"
#include "GameMonster.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
			SAFE_DELETE(actor);
	}
	_actors->clear();
}

void DevScene::Init()
{
	//GET_SINGLE(ResourceManager)->LoadTexture(L"BG", L"Sprite\\BG.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Snake", L"Sprite\\Monster\\Snake.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Hit", L"Sprite\\Effect\\Hit.bmp", RGB(0, 0, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	LoadMap();
	LoadPlayer();
	LoadMonster();
	LoadProjectile();
	LoadEffect();
	LoadTilemap();

	SpawnObject<Player>(VectorInt{ 5,5 });
	SpawnObject<GameMonster>(VectorInt{ 7,7 });

	//{
	//	Player* player = new Player();
	//	//{
	//	//	BoxCollider* collider = new BoxCollider();
	//	//	collider->SetSize({ 100,100 });
	//	//	collider->SetCollisionLayer(CLT_OBJECT);
	//	//	collider->AddCollisionFlagLayer(CLT_GROUND);
	//	//	//collider->AddCollisionFlagLayer(CLT_OBJECT);
	//	//	//collider->SetRadius(50);
	//	//	player->AddComponent(collider);
	//	//	GET_SINGLE(CollisionManager)->AddCollider(collider);
	//	//}
	//	AddActor(player);
	//}

	//{
	//	Actor* player = new Actor();
	//	player->SetLayer(LAYER_OBJECT);
	//	player->SetPos({ 500,200 });
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 100,100 });
	//		collider->SetCollisionLayer(CLT_GROUND);
	//		player->SetPos({ 400,200 });
	//		player->AddComponent(collider);
	//		GET_SINGLE(CollisionManager)->AddCollider(collider);
	//	}
	//	AddActor(player);
	//}

	//{
	//	Actor* player = new Actor();
	//	player->SetLayer(LAYER_OBJECT);
	//	player->SetPos({ 200,400 });
	//	{
	//		BoxCollider* collider = new BoxCollider();
	//		collider->SetSize({ 10000,100 });
	//		collider->SetCollisionLayer(CLT_GROUND);
	//		uint32 flag = 0;

	//		collider->SetCollsionFlag(flag);

	//		player->AddComponent(collider);
	//		GET_SINGLE(CollisionManager)->AddCollider(collider);
	//	}
	//	AddActor(player);
	//}

	//{
	//	TestPanel* ui = new TestPanel();
	//	_uis.push_back(ui);
	//}

	// BGM 추가
	//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	//{
		//Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		//sound->Play(true);

		//GET_SINGLE(SoundManager)->Play(L"BGM");
	//}
	Super::Init();
	//_go->Start();
}

void DevScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// 거리 = 시간 * 속도

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Tilemap\\Tilemap01.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap01.txt");
	}

	TickMonsterSpawn();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void DevScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);

	GameMonster* monster = dynamic_cast<GameMonster*>(actor);
	if (monster)
		_monsterCount++;
}

void DevScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);

	GameMonster* monster = dynamic_cast<GameMonster*>(actor);
	if (monster)
		_monsterCount--;
}

void DevScene::LoadMap()
{
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const VectorInt size = sprite->GetSize();
		background->SetPos(Vector(size.x / 2, size.y / 2));

		AddActor(background);
	}
}

void DevScene::LoadPlayer()
{
	// IDLE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleUp");
		fb->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleDown");
		fb->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 0, 0.5f });
	}
	// MOVE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp");
		fb->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown");
		fb->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 1, 0.5f });
	}
	// SKILL
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp");
		fb->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown");
		fb->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	// BOW
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowUp");
		fb->SetInfo({ texture, L"FB_BowUp", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowDown");
		fb->SetInfo({ texture, L"FB_BowDown", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowLeft");
		fb->SetInfo({ texture, L"FB_BowLeft", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BowRight");
		fb->SetInfo({ texture, L"FB_BowRight", {200, 200}, 0, 7, 5, 0.5f, false });
	}
	// STAFF
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffUp");
		fb->SetInfo({ texture, L"FB_StaffUp", {200, 200}, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffDown");
		fb->SetInfo({ texture, L"FB_StaffDown", {200, 200}, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffLeft");
		fb->SetInfo({ texture, L"FB_StaffLeft", {200, 200}, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_StaffRight");
		fb->SetInfo({ texture, L"FB_StaffRight", {200, 200}, 0, 10, 6, 0.5f, false });
	}
}

void DevScene::LoadMonster()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeUp");
		fb->SetInfo({ texture, L"FB_SnakeUp", {100, 100}, 0, 3, 3, 0.5f, true });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeDown");
		fb->SetInfo({ texture, L"FB_SnakeDown", {100, 100}, 0, 3, 0, 0.5f, true });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeLeft");
		fb->SetInfo({ texture, L"FB_SnakeLeft", {100, 100}, 0, 3, 2, 0.5f, true });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SnakeRight");
		fb->SetInfo({ texture, L"FB_SnakeRight", {100, 100}, 0, 3, 1, 0.5f, true });
	}
}

void DevScene::LoadProjectile()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowUp");
		fb->SetInfo({ texture, L"FB_ArrowUp", {100, 100}, 0, 0, 3, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowDown");
		fb->SetInfo({ texture, L"FB_ArrowDown", {100, 100}, 0, 0, 0, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowLeft");
		fb->SetInfo({ texture, L"FB_ArrowLeft", {100, 100}, 0, 0, 2, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowRight");
		fb->SetInfo({ texture, L"FB_ArrowRight", {100, 100}, 0, 0, 1, 0.5f, false });
	}
}

void DevScene::LoadEffect()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Hit");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Hit");
		fb->SetInfo({ texture, L"FB_Hit", {50, 47}, 0, 5, 0, 0.5f, false });
	}
}

void DevScene::LoadTilemap()
{
	{
		TileMapActor* actor = new TileMapActor();
		AddActor(actor);
		_tilemapActor = actor;
		{
			auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			tm->SetMapSize({ 63,43 });
			tm->SetTileSize(48);

			GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap01.txt");

			_tilemapActor->SetTilemap(tm);
			_tilemapActor->SetShowDebug(false);
		}
	}
}

bool DevScene::CanGo(VectorInt cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	TileMap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return false;

	Tile* tile = tm->GetTileAt(cellPos);
	if (tile == nullptr)
		return false;

	// 몬스터 충돌?
	if (GetCreatureAt(cellPos) != nullptr)
		return false;

	return tile->value != 1;
}

Vector DevScene::ConvertPos(VectorInt cellPos)
{
	Vector ret = {};

	if (_tilemapActor == nullptr)
		return ret;

	TileMap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	int32 size = tm->GetTileSize();
	Vector pos = _tilemapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + (size / 2);
	ret.y = pos.y + cellPos.y * size + (size / 2);

	return ret;
}

VectorInt DevScene::GetRandomEmptyCellPos()
{
	VectorInt ret = { -1,-1 };

	if (_tilemapActor == nullptr)
		return ret;

	TileMap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	VectorInt size = tm->GetMapSize();
	
	// 몇번이나 시도 할지는 정책을 정해야함 (매우 오래 걸릴 수 있음)
	while (true)
	{
		int32 x = rand() % size.x;
		int32 y = rand() % size.y;
		VectorInt cellPos{ x,y };

		if (CanGo(cellPos))
			return cellPos;
	}


	return ret;
}

void DevScene::TickMonsterSpawn()
{
	if (_monsterCount < DESIRED_MONSTER_COUNT)
		SpawnOnjectAtRandomPos<GameMonster>();
}
