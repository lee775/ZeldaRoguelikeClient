#pragma once
#include "ResourcesBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;
	wstring name;
	VectorInt size = {};
	int32 start = 0;
	int32 end = 0;
	int32 line = 0;
	float duration = 1.f;
	bool loop = true;
};

class Flipbook : public ResourcesBase
{
public:
	Flipbook();
	virtual ~Flipbook();

	void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() { return _info; }

private:
	FlipbookInfo _info;
	float _sumTime = 0.f;
	int32 _idx = 0;
};

