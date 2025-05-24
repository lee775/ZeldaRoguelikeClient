#pragma once
#include "Scene.h"

class Actor;
class MainGameObject;
class UI;

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void AddActor(Actor* actor) override;
	virtual void RemoveActor(Actor* actor) override;

	void LoadMap();
	void LoadPlayer();
	void LoadMonster();
	void LoadProjectile();
	void LoadEffect();
	void LoadTilemap();

	template<typename T>
	T* SpawnObject(VectorInt pos)
	{
		// Type-Trait
		// T타입이 MainGameObject로 변환이 되는지 컴파일 타임에 확인
		auto isGameObject = std::is_convertible_v<T*, MainGameObject*>;
		assert(isGameObject);

		T* ret = new T();
		ret->SetCellPos(pos, true);
		AddActor(ret);

		ret->BeginPlay();

		return ret;
	}

	template<typename T>
	T* SpawnOnjectAtRandomPos()
	{
		VectorInt randPos = GetRandomEmptyCellPos();
		return SpawnObject<T>(randPos);
	}

	bool CanGo(VectorInt cellPos);
	Vector ConvertPos(VectorInt cellPos);
	VectorInt GetRandomEmptyCellPos();

	//	void AddActor(Actor* actor);
	//	void RemoveActor(Actor* actor);
	//
	//public:
	//	// TEST
	//	Pos _playerPos = { 300,300 };
	//	float _speed = 1000;
	//
	//	//Actor* _background;
	//	//Actor* _player;
	//
	//	vector<Actor*> _actors[LAYER_MAXCOUNT];
	//
	//	vector<UI*> _uis;
	//
	//	GameObject* _go;

private:
	void TickMonsterSpawn();

private:
	const int32 DESIRED_MONSTER_COUNT = 20;
	int32 _monsterCount = 0;

	class TileMapActor* _tilemapActor = nullptr;
};