#pragma once

class ResourceBase;
class Texture;
class Sprite;
class Flipbook;
class TileMap;
class Sound;

//class LineMesh;

class ResourceManager
{
	DECLARE_SINGLE(ResourceManager);
public:
	~ResourceManager();

public:
	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	//const LineMesh* GetLineMesh(wstring key);
	const fs::path& GetResourcePath() { return _resourcePath; }

	Texture* GetTexture(const wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Flipbook* GetFlipbook(const wstring& key) { return _flipbooks[key]; }
	Flipbook* CreateFlipbook(const wstring& key);

	TileMap* GetTilemap(const wstring& key) { return _tilemaps[key]; }
	TileMap* CreateTilemap(const wstring& key);
	void SaveTilemap(const wstring& key, const wstring& path);
	TileMap* LoadTilemap(const wstring& key, const wstring& path);

	Sound* GetSound(const wstring& key) { return _sounds[key]; }
	Sound* LoadSound(const wstring& key, const wstring& path);

private:
	//unordered_map<wstring, LineMesh*> _lineMeshes;
	HWND _hwnd;
	fs::path _resourcePath;

	unordered_map<wstring, Texture*> _textures;
	unordered_map<wstring, Sprite*> _sprites;
	unordered_map<wstring, Flipbook*> _flipbooks;
	unordered_map<wstring, TileMap*> _tilemaps;
	unordered_map<wstring, Sound*> _sounds;
};

