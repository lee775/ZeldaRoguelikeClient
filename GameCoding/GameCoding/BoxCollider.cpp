#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();
}

void BoxCollider::TickComponent()
{
	Super::TickComponent();
}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_showDebug)
		return;

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vector pos = GetOwner()->GetPos();

	pos.x -= (cameraPos.x - GWinSizeX / 2);
	pos.y -= (cameraPos.y - GWinSizeY / 2);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, _size.x, _size.y);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBoxToBox(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionSphereToBox(static_cast<SphereCollider*>(other), this);
	}
}

RECT BoxCollider::GetRect()
{
	Vector pos = GetOwner()->GetPos();
	Vector size = GetSize();

	RECT rect =
	{
		(int32)(pos.x - (size.x / 2)),
		(int32)(pos.y - (size.y / 2)),
		(int32)(pos.x + (size.x / 2)),
		(int32)(pos.y + (size.y / 2)),
	};

	return rect;
}
