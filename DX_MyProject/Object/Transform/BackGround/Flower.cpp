#include "framework.h"

vector<shared_ptr<const Frame>> Flower::flowerFrames;
int Flower::flowerUseCnt = 0;

Flower::Flower()
	:spawn_rate(0.35f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	if (flowerFrames.empty())
	{
		InitFrame();
	}

	clips.emplace_back(make_shared<const Clip>(flowerFrames, Clip::CLIP_TYPE::END, 1 / 4.0f));
	renderSize = Vector2(29.0f, 38.0f)*1.2f;
	
	ChangePos();

	++flowerUseCnt;
}

Flower::~Flower()
{
	clips.clear();
	delete CB;

	if ((--flowerUseCnt) == 0)
	{
		ClearFrame();
	}
}

void Flower::Update()
{
	clips[clipIdx]->Update();
	scale = clips[clipIdx]->GetFrameSize() * renderSize / clips[clipIdx]->GetFrameOriginSize();
	
	Vector2 before_pos = pos;
	pos = target->pos + offset;
	WorldUpdate();

	if ((before_pos - pos).GetLength() > 1.0f)
	{
		ChangePos();
	}
}

void Flower::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	clips[clipIdx]->Render();
}

void Flower::PostRender()
{
}

void Flower::SetIndex(int idx)
{
	clipIdx = idx;
}

void Flower::ChangePos()
{
	pair<int, int> nowPos = make_pair((int)pos.x, (int)pos.y);
	if (activeRecord.find(nowPos) == activeRecord.end())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawn_rate)
		{
			is_active = true;
			SetIndex(Random::Get()->GetRandomInt(0, 5));
			activeRecord[nowPos] = true;
			clipRecord[nowPos] = clipIdx;
		}
		else
		{
			is_active = false;
			activeRecord[nowPos] = false;
		}
	}
	else
	{
		is_active = activeRecord[nowPos];
		SetIndex(clipRecord[nowPos]);
	}
}

void Flower::InitFrame()
{
	if (!(flowerFrames.empty())) return;

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";

	for (int i = 0; i < 6; i++)
	{
		flowerFrames.emplace_back(make_shared<const Frame>(file, 4.0f + 31.0f * i, 74.0f, 29.0f, 38.0f));
	}
}

void Flower::ClearFrame()
{

	flowerFrames.clear();
}
