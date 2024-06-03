#include "framework.h"

Tree::Tree()
	:spawn_rate(0.85f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";
	vector<Frame*> frames;
	// leaf tree
	frames.push_back(new Frame(file, 4.0f, 151.0f, 137.0f, 133.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// leaf less tree
	frames.push_back(new Frame(file, 141.0f, 151.0f, 116.0f, 127.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	collider = new RectCollider(Vector2(58.0f, 30.0f));

	ChangePos();
}

Tree::~Tree()
{
	for (auto c : clips)
		delete c;

	delete collider;
	delete CB;
}

void Tree::Update()
{
	//if (!is_active)return;

	clips[clip_idx]->Update();
	scale = clips[clip_idx]->GetFrameSize() * render_size / clips[clip_idx]->GetFrameOriginSize();
	Vector2 before_pos = pos;
	pos = target->pos + offset;
	WorldUpdate();

	collider->pos = pos + collider_offset;
	collider->WorldUpdate();

	if ((before_pos - pos).GetLength() > 1.0f)
	{
		ChangePos();
	}
}

void Tree::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	clips[clip_idx]->Render();
	collider->Render();
}

void Tree::PostRender()
{
}

void Tree::SetIndex(int idx)
{
	switch (idx)
	{
	case 0:
		clip_idx = 0;
		render_size = Vector2(137.0f, 133.0f) * 1.5f;
		collider_offset = Vector2(0, 70.0f);
		break;
	case 1:
		clip_idx = 1;
		render_size = Vector2(116.0f, 127.0f) * 1.5f;
		collider_offset = Vector2(0, 70.0f);
		break;
	default:
		break;
	}
}

void Tree::ChangePos()
{
	pair<int, int> now_pos = make_pair((int)pos.x, (int)pos.y);
	if (active_record.find(now_pos)==active_record.end())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawn_rate)
		{
			is_active = true;
			SetIndex(Random::Get()->GetRandomInt(0, 1));
			collider->SetActive(true);
			active_record[now_pos] = true;
			clip_record[now_pos] = clip_idx;
		}
		else
		{
			is_active = false;
			collider->SetActive(false);
			active_record[now_pos] = false;
		}
	}
	else
	{
		is_active = active_record[now_pos];
		collider->SetActive(is_active);
		SetIndex(clip_record[now_pos]);
	}
}
