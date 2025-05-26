#pragma once
#include "ResourcesBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;    // 사용할 텍스처 (스프라이트 시트)
	wstring name;                  // 플립북 이름
	VectorInt size = {};           // 각 프레임의 크기 (너비 x 높이)
	int32 start = 0;               // 시작 프레임 인덱스
	int32 end = 0;                 // 종료 프레임 인덱스
	int32 line = 0;                // 텍스처에서 애니메이션이 그려진 라인(세로 줄)
	float duration = 1.f;          // 전체 애니메이션의 지속 시간 (초)
	bool loop = true;              // 반복 재생 여부
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

