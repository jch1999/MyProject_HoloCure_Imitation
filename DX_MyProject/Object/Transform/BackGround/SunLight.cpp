#include "framework.h"

vector<shared_ptr<const Frame>>& SunLight::GetSunLightFrames()
{
	static vector<shared_ptr<const Frame>> sunLightFrames;
	return sunLightFrames;
}

int& SunLight::GetSunLightUseCnt()
{
	static int sunLightUseCnt = 0;
	return sunLightUseCnt;
}

SunLight::SunLight(Vector2 inRenderSize)
	:BackgroundObject(inRenderSize)
{
	// 프레임은 한 번만 생성해서 공유
	if (GetSunLightFrames().empty())
	{
		InitFrame();
	}

	SetMaxIdx(GetSunLightFrames().size());

	++GetSunLightUseCnt();
}

SunLight::~SunLight()
{
	if ((--GetSunLightUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void SunLight::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetSunLightFrames()[frameIdx];

	scale = currentFrame->GetFrameSize() * renderSize / currentFrame->GetFrameOriginSize();

	pos = target->pos + offset;
	WorldUpdate();
}

void SunLight::Render()
{
	BackgroundObject::Render();

	GetSunLightFrames()[frameIdx]->Render();
}

void SunLight::InitFrame()
{
	auto& sunLightFrames = GetSunLightFrames();
	if (!(sunLightFrames.empty())) return;

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";


	for (int i = 0; i < 2; i++)
	{
		sunLightFrames.emplace_back(make_shared<const Frame>(file, 4.0f + 642.0f * i, 1642.0f, 640.0f, 360.0f));
	}
}

void SunLight::ClearFrame()
{
	GetSunLightFrames().clear();
}

void SunLight::SetIndex(int inIdx)
{
	BackgroundObject::SetIndex(inIdx);

	if(inIdx==0)
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
	else
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.35f);
}
