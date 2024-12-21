#include "framework.h"

vector<shared_ptr<const Frame>> SunLight::SunLightFrames;
int SunLight::SunLightUseCnt=0;

SunLight::SunLight()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	// �������� �� ���� �����ؼ� ����
	if (SunLightFrames.empty())
	{
		Init();
	}
	
	clips.push_back(make_shared<Clip>(SunLightFrames, Clip::CLIP_TYPE::LOOP, 1));

	render_size = Vector2(WIN_WIDTH, WIN_HEIGHT);

	++SunLightUseCnt;
}

SunLight::~SunLight()
{
	clips.clear();

	delete CB;

	if ((--SunLightUseCnt) == 0)
	{
		SunLightFrames.clear();
	}
}

void SunLight::Init()
{
	SunLightFrames.clear();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";


	for (int i = 0; i < 2; i++)
	{
		SunLightFrames.push_back(make_shared<const Frame>(file, 4.0f + 642.0f * i, 1642.0f, 640.0f, 360.0f));
	}
}

void SunLight::Update()
{
	if (!is_active)return;

	clips[clip_idx]->Update();
	scale = clips[clip_idx]->GetFrameSize() * render_size / clips[clip_idx]->GetFrameOriginSize();

	pos = target->pos + offset;
	WorldUpdate();
}

void SunLight::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	clips[clip_idx]->Render();
}

void SunLight::PostRender()
{
}

void SunLight::SetIndex(int idx)
{
	clip_idx = idx;
	if(clip_idx==0)
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
	else
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.35f);
}
