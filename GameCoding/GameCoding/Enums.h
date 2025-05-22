#pragma once

enum class SceneType
{
	None,
	DevScene,
	GameScene,
	EditScene,

	//MenuScene,
	//FortressScene
};

enum class PlayerType
{
	CanonTnak,
	MissileTank
};

enum Dir
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_UI,
	LAYER_OBJECT,

	LAYER_MAXCOUNT
};

enum class ColliderType
{
	Box,
	Sphere,

};

enum COLLISION_LAYER_TYPE
{
	CLT_OBJECT = 1,
	CLT_GROUND,
	CLT_WALL,


	CLT_MAX
};