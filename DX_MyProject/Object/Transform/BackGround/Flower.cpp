#include "framework.h"

Flower::Flower()
	:spawn_rate(0.35f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";
	vector<Frame*> frames;
	for (int i = 0; i < 6; i++)
	{
		frames.push_back(new Frame(file, 4.0f + 31.0f * i, 74.0f, 29.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
		frames.clear();
	}
	render_size = Vector2(29.0f, 38.0f);
	is_active = true;
}

Flower::~Flower()
{
}

void Flower::Update()
{
	if (!is_active)return;

	clips[clip_idx]->Update();
	scale = clips[clip_idx]->GetFrameSize() * render_size / clips[clip_idx]->GetFrameOriginSize();
	pos = target->pos + offset;
	WorldUpdate();
}

void Flower::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	clips[clip_idx]->Render();
}

void Flower::PostRender()
{
}

void Flower::SetIndex(int idx)
{
	clip_idx = idx;
}

void Flower::SetActive(bool active)
{
	if (active)
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawn_rate)
		{
			is_active = active;
			SetIndex(Random::Get()->GetRandomInt(0, 5));
		}
		else
		{
			is_active = false;
		}
	}
	else
		is_active = false;
}
