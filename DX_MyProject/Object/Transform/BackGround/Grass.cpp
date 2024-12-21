#include "framework.h"

vector<shared_ptr<const Frame>> Grass::grassFrames;
int Grass::grassUseCnt = 0;

Grass::Grass()
	:spawn_rate(0.05f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	if (grassFrames.empty())
	{
		Init();
	}

	frame = grassFrames[0];

	renderSize = Vector2(29.0f, 30.0f);
	ChangePos();

	++grassUseCnt;
}

Grass::~Grass()
{
	delete CB;

	if ((--grassUseCnt) == 0)
	{
		grassFrames.clear();
	}
}

void Grass::Init()
{
	grassFrames.clear();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";
	
	for (int i = 0; i < 2; i++)
	{
		frame=make_shared<const Frame>(file, 190.0f + 31.0f * i, 74.0f, 29.0f, 30.0f);
	}
}

void Grass::Update()
{
	scale = frame->GetFrameSize() * renderSize / frame->GetFrameOriginSize();
	
	Vector2 before_pos = pos;
	pos = target->pos + offset;
	WorldUpdate();

	if ((before_pos - pos).GetLength() > 1.0f)
	{
		ChangePos();
	}
}

void Grass::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	frame->Render();
}

void Grass::PostRender()
{
}

void Grass::SetIndex(int idx)
{
	frameIdx = idx;
	frame = grassFrames[idx];
}

void Grass::ChangePos()
{
	pair<int, int> now_pos = make_pair((int)pos.x, (int)pos.y);
	if (activeRecord.find(now_pos) == activeRecord.end())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawn_rate)
		{
			is_active = true;
			SetIndex(Random::Get()->GetRandomInt(0, 1));
			activeRecord[now_pos] = true;
			clipRecord[now_pos] = frameIdx;
		}
		else
		{
			is_active = false;
			activeRecord[now_pos] = false;
		}
	}
	else
	{
		is_active = activeRecord[now_pos];
		SetIndex(clipRecord[now_pos]);
	}
}


