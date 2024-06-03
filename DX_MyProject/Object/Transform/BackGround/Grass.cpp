#include "framework.h"

Grass::Grass()
	:spawn_rate(0.05f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";
	vector<Frame*> frames;
	for (int i = 0; i < 2; i++)
	{
		frames.push_back(new Frame(file, 190.0f + 31.0f * i, 74.0f, 29.0f, 30.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
		frames.clear();
	}
	render_size = Vector2(29.0f, 30.0f);
	ChangePos();
}

Grass::~Grass()
{
	for (auto c : clips)
		delete c;
	delete CB;
}

void Grass::Update()
{
	clips[clip_idx]->Update();
	scale = clips[clip_idx]->GetFrameSize() * render_size / clips[clip_idx]->GetFrameOriginSize();
	
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
	clips[clip_idx]->Render();
}

void Grass::PostRender()
{
}

void Grass::SetIndex(int idx)
{
	clip_idx = idx;
}

void Grass::ChangePos()
{
	pair<int, int> now_pos = make_pair((int)pos.x, (int)pos.y);
	if (active_record.find(now_pos) == active_record.end())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawn_rate)
		{
			is_active = true;
			SetIndex(Random::Get()->GetRandomInt(0, 1));
			active_record[now_pos] = true;
			clip_record[now_pos] = clip_idx;
		}
		else
		{
			is_active = false;
			active_record[now_pos] = false;
		}
	}
	else
	{
		is_active = active_record[now_pos];
		SetIndex(clip_record[now_pos]);
	}
}


