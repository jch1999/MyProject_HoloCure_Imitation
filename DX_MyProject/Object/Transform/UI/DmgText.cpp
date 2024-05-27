#include "framework.h"

DmgText::DmgText()
	:speed(15.0f)
	,move_dir(Vector2(0,0))
	,lifeTime(1.5f)
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	// normal dmg clip
	for (int i = 0; i < 9; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 7, 484, 5, 7));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// crt dmg clip
	for (int i = 0; i < 9; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 7, 493, 5, 7));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// ? dmg clip
	for (int i = 0; i < 9; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 7, 502, 5, 7));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}

	id = UI_ID::DMG_TEXT;
	type = UI_TYPE::DMG_TEXT; 
	ui_size = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

DmgText::~DmgText()
{
}

void DmgText::Update()
{
	if (!is_active)return;

	leftTime -= DELTA;
	if (leftTime < 0.0f)
		is_active = false;

	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, leftTime / 1.5f);
	scale = clips[clip_idx]->GetFrameSize() * Vector2(10.0f, 14.0f) / clips[clip_idx]->GetFrameOriginSize() * ui_size;
	clips[clip_idx]->Update();
	
	pos = pos + move_dir * speed * DELTA;
	WorldUpdate();
}

void DmgText::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void DmgText::PostRender()
{
}

void DmgText::SetClipIdx(int idx)
{
	switch (id)
	{
	case UI::UI_ID::DMG_TEXT:
	{
		clip_idx = idx;
	}
		break;
	case UI::UI_ID::CRT_DMG_TEXT:
	{
		clip_idx = idx + 10;
	}
		break;
	default:
		break;
	}
}

void DmgText::SetActive(bool active)
{
	UI::SetActive(active);
	leftTime = lifeTime;
}

