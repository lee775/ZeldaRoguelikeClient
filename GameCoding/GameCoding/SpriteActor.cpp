#include "pch.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"

SpriteActor::SpriteActor() : Actor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();


}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr)
		return;

	VectorInt size = _sprite->GetSize();

	// 투명값을 넣을 수 없기때문에 다른 함수를 써야함 TransparentBlt()
	//::BitBlt(hdc,
	//	0,
	//	0,
	//	size.x,
	//	size.y,
	//	_sprite->GetDC(),
	//	_sprite->GetPos().x,
	//	_sprite->GetPos().y,
	//	SRCCOPY);

	//(int32)_pos.x - size.x / 2

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x,
		size.y,
		_sprite->GetDC(), 
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		_sprite->GetTransparent());

}
