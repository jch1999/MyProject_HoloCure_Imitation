#include "framework.h"

Arrow::Arrow()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	// atk dir arrow 
	// normal clip
	frames.push_back(new Frame(file, 236, 494, 64, 64));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// fixed clip
	frames.push_back(new Frame(file, 302, 494, 64, 64));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// ? clip
	frames.push_back(new Frame(file, 368, 494, 64, 64));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	id = UI::UI_ID::ATK_ARROW;
	type = UI::UI_TYPE::ARROW;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(64.0f, 64.0f);
	ui_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

	pos = target->pos;
	WorldUpdate();
}

void Arrow::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void Arrow::PostRender()
{
}

void Arrow::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void Arrow::SetID(UI::UI_ID id)
{
	if (this->id == id)return;

	this->id = id;;
	switch (id)
	{
	case UI::UI_ID::ATK_ARROW:
	{
		clip_idx = 0;
	}
		break;
	case UI::UI_ID::ATK_ARROW_FIXED:
	{
		clip_idx = 1;
	}
	break;
	default:
		break;
	}
}
