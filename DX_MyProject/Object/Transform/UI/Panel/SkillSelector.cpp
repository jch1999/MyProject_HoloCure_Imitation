#include "framework.h"

SkillSelector::SkillSelector()
	:char_pos(Vector2(0,0)),char_interval(Vector2(10.0f,20.0f)), line_length(40)
	,name_offset(Vector2(-230.0f,-35.0f))
	,script_offset(Vector2(-180.0f,-10.0f))
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

	skill_icon = new SkillIcon();
	skill_icon->SetID(UI_ID::SKILL_LEVEL_UP_ICON);
	skill_icon->SetTarget(this);
	skill_icon->SetOffset(Vector2(-215.0f, 5.0f));
	skill_icon->SetActive(true);
	
	child_list.push_back(skill_icon);

	// text 
	skillName_text = new TextPrinter();
	skillName_text->SetTarget(this);
	skillName_text->SetOffset(name_offset);
	skillName_text->SetCharInterval(char_interval);
	skillName_text->SetLineLength(line_length);
	skillName_text->SetCharScale(Vector2(0.3f, 0.3f));

	SkillScript_text = new TextPrinter();
	SkillScript_text->SetTarget(this);
	SkillScript_text->SetOffset(script_offset);
	SkillScript_text->SetCharInterval(char_interval);
	SkillScript_text->SetLineLength(line_length);
	SkillScript_text->SetCharScale(Vector2(0.3f, 0.3f));

	child_list.push_back(skillName_text);
	child_list.push_back(SkillScript_text);

	id = UI::UI_ID::SELECTOR;
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
	ImGui::Text("Now Skill ID : %d", skill_id);
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
	skill_icon->SetSkillID(skill_id);
	
	SetText();
}

void SkillSelector::SetText()
{
	int text_idx = 0;
	if (skill_id != -1)
	{
		Skill* skill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skill_id);
		

		if (skill->GetLevelUpAble())
		{
			string name = skill->GetSkillName() + " LV "+ to_string(skill->GetLevel() + 1);
			string scripts = skill->GetScript();
			skillName_text->SetText(name);
			SkillScript_text->SetText(scripts);
			skillName_text->SetActive(true);
			SkillScript_text->SetActive(true);
		}
		else
		{
			string name = skill->GetSkillName() + " LV MAX";
			skillName_text->SetText(name);
			skillName_text->SetActive(true);
			SkillScript_text->SetActive(false);
		}
		
	}
	else
	{
		skillName_text->SetActive(false);
		SkillScript_text->SetActive(false);
	}
}
