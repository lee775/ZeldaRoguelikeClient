#include "pch.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::BeginPlay()
{
}

void SpriteRenderer::TickComponent()
{
}

void SpriteRenderer::Render(HDC hdc)
{
	if (_sprite == nullptr)
		return;

	VectorInt size = _sprite->GetSize();

	::BitBlt(hdc,
		0,
		0,
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		SRCCOPY);
}
