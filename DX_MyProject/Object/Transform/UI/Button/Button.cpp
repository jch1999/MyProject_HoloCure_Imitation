#include "framework.h"

Button::Button()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;

	// idle clip
	frames.push_back(new Frame(file, 250.0f, 2668.0f, 180.0f, 30.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// active clip
	frames.push_back(new Frame(file, 250.0f, 2698, 180.0f, 30.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	btnText = new TextPrinter();
	btnText->SetTarget(this);
	btnText->SetOffset(this->ui_size / 2.0f * this->ui_scale);
	btnText->SetTextInfo(Vector2(0.3f, 0.3f), Vector2(10.0f, 20.0f));
	btnText->SetActive(true);
	child_list.push_back(btnText);

	id = UI::UI_ID::BUTTON;
	type = UI::UI_TYPE::BUTTON;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(180.0f, 30.0f);
	ui_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

Button::~Button()
{
}

void Button::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();

	for (auto c : child_list)
		c->Update();
}

void Button::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();

	for (auto c : child_list)
		c->Render();
}

void Button::PostRender()
{
	if (!is_active)return;
}

void Button::SetState(UI::UI_STATE state)
{
	this->state = state;
	switch (state)
	{
	case UI::UI_STATE::IDLE:
		SetClipIdx(1);
		SetColor(Float4(0.5f, 0.5f, 0.5f, 0.5f));
		break;
	case UI::UI_STATE::ACTIVE:
		SetClipIdx(0);
		SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
}

void Button::SetID(UI::UI_ID id)
{
	this->id = id;
}
