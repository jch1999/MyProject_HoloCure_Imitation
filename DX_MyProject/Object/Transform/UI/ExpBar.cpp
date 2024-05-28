#include "framework.h"

ExpBar::ExpBar()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	// ExpBar_Back_Frame
	frames.push_back(new Frame(file, 4, 52, 650, 26));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// ExpBar_Front_Frame
	frames.push_back(new Frame(file, 4, 80, 650, 26));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// ExpBar
	Vector2 initPos(666, 52);
	for (int i = 0; i < 61; i++)
	{
		frames.push_back(new Frame(file, initPos.x, initPos.y + i*28.0f, 650, 26));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}

	id = UI_ID::EXP_BAR;
	type = UI_TYPE::EXP_BAR; 
	ui_size = Vector2(WIN_WIDTH+20.0f, 40.0f);
	ui_scale = Vector2(1, 1);
	offset = Vector2(WIN_CENTER_X+10.0f, 20.0f);
	is_active = false;
}

ExpBar::~ExpBar()
{
}

void ExpBar::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();
	pos = target->pos + offset;
	WorldUpdate();
}

void ExpBar::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void ExpBar::PostRender()
{
}

void ExpBar::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void ExpBar::SetID(UI::UI_ID id)
{
	this->id = id;
	switch (id)
	{
	case UI_ID::EXP_BAR_BACK:
	{
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
		clip_idx = 0;
	}
		break;
	case UI_ID::EXP_BAR:
	{
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
	}
		break;
	case UI_ID::EXP_BAR_FRONT:
	{
		clip_idx = 1;
	}
		break;
	default:
		break;
	}
}

void ExpBar::SetExpRate(float rate)
{
	expRate = rate;
	clip_idx = 2 + (int)(rate * 61.0f);

	int a;
}
