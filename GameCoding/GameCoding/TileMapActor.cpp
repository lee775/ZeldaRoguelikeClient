#include "pch.h"
#include "TileMapActor.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TileMap.h"
#include "Sprite.h"
#include "ResourceManager.h"

TileMapActor::TileMapActor()
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TileMapActor::Tick()
{
	Super::Tick();

	TilePicking();
}

void TileMapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr)
		return;

	if (_showDebug == false)
		return;

	const VectorInt mapSize = _tilemap->GetMapSize();
	const int32 tileSize = _tilemap->GetTileSize();

	vector<vector<Tile>>& tiles = _tilemap->GetTiles();

	Sprite* sprite0 = GET_SINGLE(ResourceManager)->GetSprite(L"Tile0");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// �ø� : ������ �� �ֵ鸸 �����ֱ� (ī�޶� ������ �κи� ����ϱ�)
	int32 leftX = ((int32)cameraPos.x - GWinSizeX / 2);
	int32 leftY = ((int32)cameraPos.y - GWinSizeY / 2);
	int32 rightX = ((int32)cameraPos.x + GWinSizeX / 2);
	int32 rightY = ((int32)cameraPos.y + GWinSizeY / 2);

	int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / TILE_SIZEY;
	int32 endX = (rightX - _pos.x) / TILE_SIZEX;
	int32 endY = (rightY - _pos.y) / TILE_SIZEY;


	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.x)
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;

			switch (tiles[y][x].value)
			{
			case 0:
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					sprite0->GetDC(),
					sprite0->GetPos().x,
					sprite0->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					sprite0->GetTransparent()
					);
				break;
			case 1:
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent()
				);
				break;
			}
		}
	}
}

void TileMapActor::TilePicking()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({ x,y });
		if (tile->value == 0)
			tile->value = 1;
		else if (tile->value == 1)
			tile->value = 0;
	}
}
