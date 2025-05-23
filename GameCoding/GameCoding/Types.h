#pragma once

#include <cmath>
#include <Windows.h>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct Stat
{
	int32 hp = 0;
	int32 maxHp = 0;
	int32 attack = 0;
	int32 defence = 0;
	float speed = 0;
};

struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) :x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}

	bool operator==(const Vector& other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector& other)
	{
		return x != other.x || y != other.y;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		if (length < 0.00000001f)
			return;

		x /= length;
		y /= length;
	}

	// 내적
	float Dot(Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// 외적
	float Cross(Vector& other)
	{
		return x * other.y - y * other.x;
	}

	float x = 0;
	float y = 0;
};

struct VectorInt
{
	VectorInt() {}
	VectorInt(int32 x, int32 y) : x(x), y(y) {}
	VectorInt(POINT pt) :x((int32)pt.x), y((int32)pt.y) {}

	VectorInt operator+(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	VectorInt operator-(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	VectorInt operator*(int32 value)
	{
		VectorInt ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}

	void operator+=(const VectorInt& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const VectorInt& other)
	{
		x -= other.x;
		y -= other.y;
	}

	bool operator==(const VectorInt& other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const VectorInt& other)
	{
		return !(*this == other);
	}

	void operator*=(int32 value)
	{
		x *= value;
		y *= value;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	// 내적
	float Dot(Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// 외적
	float Cross(Vector& other)
	{
		return x * other.y - y * other.x;
	}

	int32 x = 0;
	int32 y = 0;
};

using Pos = Vector;