#include "framework.h"

HPBar::HPBar()
	:leftTime(0.0f)
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	// now hp clip
	frames.push_back(new Frame(file, 4, 484, 129, 6));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// before hp clip
	frames.push_back(new Frame(file, 4, 492, 129, 7));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	id = UI::UI_ID::HP_BAR;
	type = UI::UI_TYPE::HP_BAR;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

HPBar::~HPBar()
{
	delete frame;
}

void HPBar::Update()
{
	if (!is_active)return;
	
	switch (state)
	{
	case UI::UI_STATE::IDLE:
	{
		switch (id)
		{
		case UI_ID::HP_BAR:
		{
			if (ui_size.x <= 0.99f)
			{
				SetState(UI_STATE::ACTIVE);
			}
		}
		break;
		case UI_ID::HP_BAR_BACK:
			if (leftTime > 0.0f)
			{
				SetState(UI_STATE::ACTIVE);
			}
		}
		
	}
		break;
	case UI::UI_STATE::ACTIVE:
	{
		switch (id)
		{
		case UI_ID::HP_BAR:
		{
			if (ui_size.x > 0.99f)
			{
				SetState(UI_STATE::IDLE);
			}
		}
		break;
		case UI_ID::HP_BAR_BACK:
			leftTime -= DELTA;
			if (leftTime < 0.0f)
			{
				SetState(UI_STATE::IDLE);
			}
		}
	}
		break;
	default:
		break;
	}

	scale = clips[clip_idx]->GetFrameSize() * Vector2(40.0f, 5.0f) / clips[clip_idx]->GetFrameOriginSize() * ui_size;
	clips[clip_idx]->Update();
	pivot = Vector2(ui_size.x / 2.0f, 0);

	pos = target->pos + offset;
	WorldUpdate();
}

void HPBar::Render()
{
	if (!is_active)return;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
	{

	}
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
	//collider->Render();
}

void HPBar::PostRender()
{
	ImGui::DragFloat2("pos", (float*)&pos, 1.0f, -WIN_WIDTH, WIN_WIDTH);
	ImGui::DragFloat2("size", (float*)&size, 1.0f, -WIN_WIDTH, WIN_WIDTH);
	ImGui::DragFloat2("offset", (float*)&offset, 1.0f, -WIN_WIDTH, WIN_WIDTH);
}

void HPBar::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void HPBar::SetID(UI::UI_ID id)
{
	clip_idx = (UINT)id - (UINT)UI_ID::HP_BAR;
}
