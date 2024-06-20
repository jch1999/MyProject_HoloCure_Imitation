#include "framework.h"

ChargeEffect::ChargeEffect()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			frames.push_back(new Frame(file, 4.0f + 130.0f * j, 1058.0f + 130.0f * i, 128.0f, 128.0f));
		}
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 0.5f / 15.0f));
	frames.clear();

	type = UI_TYPE::EFFECT;
	id = UI_ID::CHARGE_EFFECT;
	state = UI_STATE::IDLE;
	ui_size = Vector2(128.0f, 128.0f);
	ui_scale = Vector2(1, 1);
	offset = Vector2(0.0f, 0.0f);
}

ChargeEffect::~ChargeEffect()
{
}

void ChargeEffect::Update()
{
	if (!is_active)return;
	
	if (target != nullptr)
		pos = target->pos + offset;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
		clips[clip_idx]->Update();
		break;
	default:
		break;
	}

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	
	WorldUpdate();
}

void ChargeEffect::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	
	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
	{
		clips[clip_idx]->Render();
	}
		break;
	default:
		break;
	}
}

void ChargeEffect::PostRender()
{
}

void ChargeEffect::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void ChargeEffect::SetID(UI::UI_ID id)
{
	this->id = id;
}
