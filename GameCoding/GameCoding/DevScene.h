#pragma once
#include "Scene.h"

class Actor;
class GameObject;
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

	bool CanGo(VectorInt cellPos);
	Vector ConvertPos(VectorInt cellPos);

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
	class TileMapActor* _tilemapActor = nullptr;
};

