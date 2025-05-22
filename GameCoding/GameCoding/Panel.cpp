#include "pch.h"
#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
    for (UI* child : _children)
        SAFE_DELETE(child);

    _children.clear();
}

void Panel::BeginPlay()
{
    Super::BeginPlay();

    for (UI* child : _children)
        child->BeginPlay();
}

void Panel::Tick()
{
    Super::Tick();

    for (UI* child : _children)
        child->Tick();
}

void Panel::Render(HDC hdc)
{
    Super::Render(hdc);

    for (UI* child : _children)
        child->Render(hdc);
}

void Panel::AddChild(UI* ui)
{
    if (ui == nullptr)
        return;

    _children.push_back(ui);
}

bool Panel::RemoveChild(UI* ui)
{
    _children.erase(std::remove(_children.begin(), _children.end(), ui), _children.end());
    return true;
}
