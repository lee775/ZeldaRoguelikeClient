#include "pch.h"
#include "HitEffect.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

HitEffect::HitEffect()
{
	SetLayer(LAYER_EFFECT);
}

HitEffect::~HitEffect()
{
}

void HitEffect::BeginPlay()
{
	Super::BeginPlay();

	// TODO
	UpdateAnimation();
}

void HitEffect::Tick()
{
	Super::Tick();

	// TODO
	if (IsAnimationEnded())
	{
		Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
		scene->RemoveActor(this);
	}
}

void HitEffect::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void HitEffect::UpdateAnimation()
{
	SetFlipbook(GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Hit"));
}
