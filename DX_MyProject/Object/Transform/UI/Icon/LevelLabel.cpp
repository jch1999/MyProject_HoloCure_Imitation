#include "framework.h"

LevelLabel::LevelLabel()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	Vector2 initPos(139, 533);
	for (int i = 0; i < 3; i++)
	{
		frames.push_back(new Frame(file, 139 + i * 22, 533, 20, 9));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
		frames.clear();
	}

	levelText = new LevelText();
	levelText->SetID(UI_ID::TEXT);
	levelText->SetTarget(this);
	levelText->SetOffset(Vector2(10.0f, 1.0f));
	levelText->SetClipIdx(1);
	
	id = UI::UI_ID::LEVEL_LABEL;
	type = UI::UI_TYPE::LABEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(20.0f, 9.0f);
	ui_scale = Vector2(2.0f, 2.0f);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

LevelLabel::~LevelLabel()
{
}

void LevelLabel::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale * additional_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();

	levelText->Update();
}

void LevelLabel::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	levelText->Render();
}

void LevelLabel::PostRender()
{
}

void LevelLabel::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void LevelLabel::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LevelLabel::SetLevel(int level)
{
	switch (clip_idx)
	{
	case 0:
		levelText->SetClipIdx(1 + level);
		break;
	case 1:
		levelText->SetClipIdx(11 + level);
		break;
	case 2:
		levelText->SetClipIdx(21 + level);
		break;
	}
}

void LevelLabel::SetActive(bool active)
{
	is_active = active;
	levelText->SetActive(active);
}
