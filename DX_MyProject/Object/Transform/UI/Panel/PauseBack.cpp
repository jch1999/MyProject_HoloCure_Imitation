#include "framework.h"

PauseBack::PauseBack()
{
	wstring file = L"Textures/UI/Black.png";
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 0, 0, 64, 64));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));

	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.5f);
	id = UI::UI_ID::PLAYER_ICON;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(WIN_WIDTH, WIN_HEIGHT);
	ui_scale = Vector2(1, 1);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0,0);
	is_active = true;
}

PauseBack::~PauseBack()
{
}

void PauseBack::Update()
{
	if (!is_active)return;
	switch (state)
	{
	case UI::UI_STATE::IDLE:
	{
		if (isPause)
			SetState(UI_STATE::ACTIVE);
	}
		break;
	case UI::UI_STATE::ACTIVE:
	{
		if (!isPause)
			SetState(UI_STATE::IDLE);
	}
		break;
	default:
		break;
	}

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();
}

void PauseBack::Render()
{
	if (!is_active)return;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
	{
		VS->Set();
		PS->Set();

		WB->SetVS(0);
		CB->SetPS(0);

		clips[clip_idx]->Render();
	}
		break;
	default:
		break;
	}
}

void PauseBack::PostRender()
{
}

void PauseBack::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void PauseBack::SetID(UI::UI_ID id)
{
	this->id = id;
}
