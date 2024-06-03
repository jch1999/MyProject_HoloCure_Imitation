#include "framework.h"

LevelText::LevelText()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	// level up clip
	frames.push_back(new Frame(file, 4, 534, 94, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// white number clip
	for (int i = 0; i <= 9; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 7, 484, 5, 7));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// Yellow number clip
	for (int i = 0; i <= 9; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 7, 493, 5, 7));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// Red number clip
	for (int i = 0; i <= 9; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 7, 502, 5, 7));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}

	id = UI_ID::LEVEL_TEXT;
	type = UI_TYPE::TEXT;
	ui_size = Vector2(10.0f, 14.0f);
	ui_scale = Vector2(1, 1);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

LevelText::~LevelText()
{
}

void LevelText::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();
}

void LevelText::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void LevelText::PostRender()
{
}

void LevelText::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LevelText::SetClipIdx(int idx)
{
	clip_idx = idx;
}
