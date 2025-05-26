#pragma once
#include "ResourcesBase.h"

class Texture : public ResourcesBase
{
public:
	Texture();
	virtual ~Texture();

public:
	Texture* LoadBmp(HWND hwnd, const wstring& path);
	HDC GetDC();

	void SetSize(VectorInt size) { _size = size; }
	VectorInt GetSize() { return _size; }

	void SetTransparent(uint32 transparent) { _transparent = transparent; }
	uint32 GetTransParent() { return _transparent; }

private:
	HDC _hdc = {};
	HBITMAP _bitmap = {};
	VectorInt _size = {};
	// ¸¶Á¨Å¸ »ö
	uint32 _transparent = RGB(255, 0, 255);
};

