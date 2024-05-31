#include "framework.h"

SkillSelector::SkillSelector()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;

	// unselect clip
	frames.push_back(new Frame(file, 4.0f, 2049.0f, 386.0f, 69.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// select clip
	frames.push_back(new Frame(file, 4.0f, 1979.0f, 386.0f, 69.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	skill_icon = new Icon();
	skill_icon->SetTarget(this);
	skill_icon->SetID(UI_ID::SKILL_LEVEL_UP_ICON);


	id = UI::UI_ID::LEVEL_UP_SELECTOR;
	type = UI::UI_TYPE::SELECTOR;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(386.0f, 69.0f);
	ui_scale = Vector2(1, 1);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

SkillSelector::~SkillSelector()
{
}

void SkillSelector::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale * additional_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();

	for (auto child : child_list)
		child->Update();
}

void SkillSelector::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();

	for (auto child : child_list)
		child->Render();
}

void SkillSelector::PostRender()
{
}

void SkillSelector::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void SkillSelector::SetID(UI::UI_ID id)
{
	this->id = id;
}

void SkillSelector::SetSkillID(int skill_id)
{
	this->skill_id = skill_id;

}
