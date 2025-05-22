#include "pch.h"
#include "Actor.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{
}

Collider::~Collider()
{
}

void Collider::BeginPlay()
{
}

void Collider::TickComponent()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
	uint32 layer = other->GetCollisionLayerType();
	if (_collisionFlag & (1 << layer))
		return true;

	return false;
}

bool Collider::CheckCollisionBoxToBox(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	// IntersectRect 아래 코드와 같음, 충돌 판정여부를 알려줌, 추가로 얼만큼 충돌 되어있는지도 알려줌
	RECT intersect = {};
	return ::IntersectRect(&intersect, &r1, &r2);


	//Vector p1 = b1->GetOwner()->GetPos();
	//Vector s1 = b1->GetSize();

	//Vector p2 = b2->GetOwner()->GetPos();
	//Vector s2 = b2->GetSize();

	//float minX_1 = p1.x - s1.x / 2;
	//float maxX_1 = p1.x + s1.x / 2;
	//float minY_1 = p1.y - s1.y / 2;
	//float maxY_1 = p1.y + s1.y / 2;

	//float minX_2 = p2.x - s2.x / 2;
	//float maxX_2 = p2.x + s2.x / 2;
	//float minY_2 = p2.y - s2.y / 2;
	//float maxY_2 = p2.y + s2.y / 2;

	//if (maxX_2 < minX_1)
	//	return false;

	//if (maxX_1 < minX_2)
	//	return false;

	//if (maxY_1 < minY_2)
	//	return false;

	//if (maxY_2 < minY_1)
	//	return false;

	//return true;
}

bool Collider::CheckCollisionSphereToBox(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2)
{
	Vector p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	Vector p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();
	
	Vector dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1 << layer);
}
