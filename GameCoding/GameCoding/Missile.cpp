#include "pch.h"
#include "Missile.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	// TODO : Data
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 각도 적용
	//_pos.y -= deltaTime * _stat.speed;

	// 해당 방향으로 총일이 날아감
	//_pos.x += _stat.speed * deltaTime * ::cos(_angle);
	//_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

	// 유도탄
	if (_target == nullptr)
	{
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			for (Object* object : objects)
			{
				if (object->GetObjectType() == ObjectType::Monster)
				{
					_target = object;
					break;
				}
			}
		}
	}
	else
	{
		Vector dir = _target->GetPos() - GetPos();
		dir.Normalize();

		_pos += dir * _stat.speed * deltaTime;
	}

	// 충돌 처리
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object == this)
			continue;

		if (object->GetObjectType() != ObjectType::Monster)
			continue;

		Vector p1 = GetPos();
		Vector p2 = object->GetPos();

		// 거리만 판별할꺼면 p2 p1이 서로 바뀌어도 상관없음
		Vector dir = p2 - p1;
		float dist = dir.Length();

		Vector dir2 = p1 - p2;
		float dis2t = dir2.Length();

		//const float dx = p1.x - p2.x;
		//const float dy = p1.y - p2.y;

		//float dist = ::sqrt(dx * dx + dy * dy);
		if (dist < 25)
		{
			GET_SINGLE(ObjectManager)->Remove(object);
			GET_SINGLE(ObjectManager)->Remove(this); // 괜찮은 코드가 아님
			return;
		}
	}

	// TODO
	if (_pos.y < -200)
	{
		// 위험한 코드임
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
