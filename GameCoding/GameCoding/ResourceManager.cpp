#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "TileMap.h"
#include "Sound.h"

//#include "LineMesh.h"

ResourceManager* ResourceManager::s_instance = nullptr;

ResourceManager::~ResourceManager()
{
    Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
    _hwnd = hwnd;
    _resourcePath = resourcePath;

    //{
    //    LineMesh* mesh = new LineMesh();
    //    mesh->Load(L"Player.txt");
    //    _lineMeshes[L"Player"] = mesh;
    //}
    //{
    //    LineMesh* mesh = new LineMesh();
    //    mesh->Load(L"Menu.txt");
    //    _lineMeshes[L"Menu"] = mesh;
    //}
    //{
    //    LineMesh* mesh = new LineMesh();
    //    mesh->Load(L"UI.txt");
    //    _lineMeshes[L"UI"] = mesh;
    //}
    //{
    //    LineMesh* mesh = new LineMesh();
    //    mesh->Load(L"MissileTank.txt");
    //    _lineMeshes[L"MissileTank"] = mesh;
    //}
    //{
    //    LineMesh* mesh = new LineMesh();
    //    mesh->Load(L"CanonTank.txt");
    //    _lineMeshes[L"CanonTank"] = mesh;
    //}

    // 현재경로
    //fs::current_path();
    // 상대경로
    //_resourcePath.relative_path();
    // 절대경로
    //fs::absolute(_resourcePath);
}

void ResourceManager::Clear()
{
    //for (auto mesh : _lineMeshes)
    //    SAFE_DELETE(mesh.second);

    //_lineMeshes.clear();

    for (auto& item : _textures)
        SAFE_DELETE(item.second);

    for (auto& item : _sprites)
        SAFE_DELETE(item.second);

    for (auto& item : _flipbooks)
        SAFE_DELETE(item.second);

    for (auto& item : _tilemaps)
        SAFE_DELETE(item.second);

    _textures.clear();
    _sprites.clear();
    _flipbooks.clear();
    _tilemaps.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
    if (_textures.find(key) != _textures.end())
        return _textures[key];

    fs::path fullPath = _resourcePath / path;

    Texture* texture = new Texture();
    texture->LoadBmp(_hwnd, fullPath.c_str());
    texture->SetTransparent(transparent);
    _textures[key] = texture;

    return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
    if (_sprites.find(key) != _sprites.end())
        return _sprites[key];

    if (cx == 0)
        cx = texture->GetSize().x;

    if (cy == 0)
        cy = texture->GetSize().y;

    Sprite* sprite = new Sprite(texture, x, y, cx, cy);
    _sprites[key] = sprite;

    return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
    if (_flipbooks.find(key) != _flipbooks.end())
        return _flipbooks[key];

    Flipbook* fb = new Flipbook();
    _flipbooks[key] = fb;
    return fb;
}

TileMap* ResourceManager::CreateTilemap(const wstring& key)
{
    if(_tilemaps.find(key) != _tilemaps.end())
        return _tilemaps[key];

    TileMap* tm = new TileMap();
    _tilemaps[key] = tm;

    return tm;
}

void ResourceManager::SaveTilemap(const wstring& key, const wstring& path)
{
    TileMap* tm = GetTilemap(key);

    fs::path fullPath = _resourcePath / path;
    tm->SaveFile(fullPath);
}

TileMap* ResourceManager::LoadTilemap(const wstring& key, const wstring& path)
{
    TileMap* tm = nullptr;

    if (_tilemaps.find(key) == _tilemaps.end())
        _tilemaps[key] = new TileMap();

    tm = _tilemaps[key];

    fs::path fullPath = _resourcePath / path;
    tm->LoadFile(fullPath);

    return tm;
}

Sound* ResourceManager::LoadSound(const wstring& key, const wstring& path)
{
    if (_sounds.find(key) != _sounds.end())
        return _sounds[key];

    fs::path fullPath = _resourcePath / path;

    Sound* sound = new Sound();
    sound->LoadWave(fullPath);
    _sounds[key] = sound;

    return sound;
}

//const LineMesh* ResourceManager::GetLineMesh(wstring key)
//{
//    auto findIt = _lineMeshes.find(key);
//    if (findIt == _lineMeshes.end())
//        return nullptr;
//
//    return findIt->second;
//}
