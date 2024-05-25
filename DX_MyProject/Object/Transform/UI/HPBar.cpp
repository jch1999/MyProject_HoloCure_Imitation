#include "framework.h"

HPBar::HPBar()
	:size(1.0f,1.0f)
	,hpRate(1.0f)
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4, 484, 129, 6));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	id = UI::UI_ID::HP_BAR;
	type = UI::UI_TYPE::BAR;

	is_active = true;
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
		if (hpRate < 0.99f)
		{
			SetState(UI_STATE::ACTIVE);
		}
	}
		break;
	case UI::UI_STATE::ACTIVE:
	{
		if (hpRate >= 0.99f)
		{
			SetState(UI_STATE::IDLE);
		}
	}
		break;
	default:
		break;
	}

	scale = clips[0]->GetFrameSize() * Vector2(64.5f, 4.0f) / clips[0]->GetFrameOriginSize() * size;
	clips[0]->Update();

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

		clips[0]->Render();
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
