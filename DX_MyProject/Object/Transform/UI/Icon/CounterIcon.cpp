#include "framework.h"

CounterIcon::CounterIcon()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	for (int i = 0; i < 2; i++)
	{
		frames.push_back(new Frame(file, 167.0f + 17.0f, 567.0f, 15.0f, 16.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1));
		frames.clear();
	}

	id = UI::UI_ID::COUNTER_ICON;
	type = UI::UI_TYPE::ICON;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(15.0f, 15.0f);
	ui_scale = Vector2(1.5f, 1.5f);
	additional_scale = Vector2(1.0f, 1.0f);
	offset = Vector2(0, 0);
	is_active = true;
}

CounterIcon::~CounterIcon()
{
	
}

void CounterIcon::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale * additional_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();
}

void CounterIcon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void CounterIcon::PostRender()
{
}

void CounterIcon::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void CounterIcon::SetID(UI::UI_ID id)
{
	this->id = id;
}
