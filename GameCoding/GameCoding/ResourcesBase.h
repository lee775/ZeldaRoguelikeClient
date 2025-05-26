#pragma once
class ResourcesBase
{
public:
	ResourcesBase();
	virtual ~ResourcesBase();

	virtual void LoadFile(const wstring& path);
	virtual void SaveFile(const wstring& path);
};

