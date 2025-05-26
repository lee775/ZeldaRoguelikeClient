#pragma once
#include "Actor.h"

class TileMap;

class TileMapActor : public Actor
{
	using Super = Actor;
public:
	TileMapActor();
	virtual ~TileMapActor();

	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Render(HDC hdc) override;

	void TilePicking();

	void SetTilemap(TileMap* tilemap) { _tilemap = tilemap; }
	TileMap* GetTilemap() { return _tilemap; }

	void SetShowDebug(bool showDebug) { _showDebug = showDebug; }

protected:
	TileMap* _tilemap = nullptr;
	bool _showDebug = false;
};

