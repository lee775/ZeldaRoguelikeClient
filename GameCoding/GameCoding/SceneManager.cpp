#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "GameScene.h"
#include "EditScene.h"

//#include "MenuScene.h"
//#include "FortressScene.h"

SceneManager* SceneManager::s_instance = nullptr;

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		break;
	case SceneType::EditScene:
		newScene = new EditScene();
		break;
	//case SceneType::MenuScene:
	//	newScene = new MenuScene();
	//	break;
	//case SceneType::FortressScene:
	//	newScene = new FortressScene();
	//	break;
	}

	SAFE_DELETE(_scene)

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
