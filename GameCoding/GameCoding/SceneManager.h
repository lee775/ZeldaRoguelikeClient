#pragma once
class Scene;
class MyPlayer;

class SceneManager
{
	DECLARE_SINGLE(SceneManager)

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() { return _scene; }

	class DevScene* GetDevScene();

	MyPlayer* GetMyPlayer() { return _myPlayer; }
	void SetMyPlayer(MyPlayer* myPlayer) { _myPlayer = myPlayer; }
	uint64 GetMyPlayerId();

private:
	Scene* _scene = nullptr;
	SceneType _sceneType = SceneType::None;
	MyPlayer* _myPlayer = nullptr;

public:
	Vector GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vector pos) { _cameraPos = pos; }
private:
	Vector _cameraPos = { 0, 0 };
};

