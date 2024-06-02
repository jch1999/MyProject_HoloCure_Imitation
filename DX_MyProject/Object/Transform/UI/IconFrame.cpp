#include "framework.h"

IconFrame::IconFrame()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	// weapon icon frame clip
	frames.push_back(new Frame(file, 189.0f, 1872.0f, 35.0f, 36.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// buff icon frame clip
	frames.push_back(new Frame(file, 152.0f, 1872.0f, 35.0f, 36.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// Stat iconframe clip
	frames.push_back(new Frame(file, 115.0f, 1872.0f, 35.0f, 36.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// Extra iconframe clip
	frames.push_back(new Frame(file, 4.0f, 1872.0f, 35.0f, 36.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	id = UI::UI_ID::SKILL_ICON_FRAME;
	type = UI::UI_TYPE::FRAME;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(35.0f, 36.0f);
	ui_scale = Vector2(1, 1);
	offset = Vector2(3, 3);
	is_active = false;
}

IconFrame::~IconFrame()
{
}

void IconFrame::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();
}

void IconFrame::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void IconFrame::PostRender()
{
}
