#pragma once
#include "ResourcesBase.h"

class Texture;

struct FlipbookInfo
{
	Texture* texture = nullptr;    // ����� �ؽ�ó (��������Ʈ ��Ʈ)
	wstring name;                  // �ø��� �̸�
	VectorInt size = {};           // �� �������� ũ�� (�ʺ� x ����)
	int32 start = 0;               // ���� ������ �ε���
	int32 end = 0;                 // ���� ������ �ε���
	int32 line = 0;                // �ؽ�ó���� �ִϸ��̼��� �׷��� ����(���� ��)
	float duration = 1.f;          // ��ü �ִϸ��̼��� ���� �ð� (��)
	bool loop = true;              // �ݺ� ��� ����
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

