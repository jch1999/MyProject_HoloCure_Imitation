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
	for (int i = 0; i < 80; i++)
	{
		Text* text = new Text();
		text->SetID(UI_ID::TEXT);
		text->SetTarget(this);
		text->SetScale(Vector2(0.3f, 0.3f));
		text_vec.push_back(text);
		child_list.push_back(text);
	}

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
	Skill* skill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skill_id);
	string name = skill->GetSkillName();
	string scripts = skill->GetScript();

	char_pos = Vector2(0, 0);
	int text_idx = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] != ' ')
		{
			text_vec[text_idx]->SetText(name[i]);
			text_vec[text_idx]->SetOffset(name_offset + char_interval * char_pos);
			text_vec[text_idx]->SetActive(true);
			text_idx++;
		}

		char_pos.x++;
	}
	// LV Ç¥½Ã
	{
		char_pos.x += 2;
		text_vec[text_idx]->SetText('L');
		text_vec[text_idx]->SetOffset(name_offset + char_interval * char_pos);
		text_vec[text_idx]->SetActive(true);
		char_pos.x += 1;
		text_idx++;
		text_vec[text_idx]->SetText('V');
		text_vec[text_idx]->SetOffset(name_offset + char_interval * char_pos);
		text_vec[text_idx]->SetActive(true);
		char_pos.x += 2;
		text_idx++;
		text_vec[text_idx]->SetText('0' + skill->GetLevel() + 1);
		text_vec[text_idx]->SetOffset(name_offset + char_interval * char_pos);
		text_vec[text_idx]->SetActive(true);
		char_pos.x += 1;
		text_idx++;
	}

	char_pos = Vector2(0, 0);
	for (int i = 0; i < scripts.length(); i++)
	{
		if (text_idx >= text_vec.size())
		{
			for (int j = 0; j < 10; j++)
			{
				Text* text = new Text();
				text->SetID(UI_ID::TEXT);
				text->SetTarget(this);
				text->SetScale(Vector2(0.3f, 0.3f));
				text_vec.push_back(text);
				child_list.push_back(text);
			}
		}

		if (scripts[i] != ' ')
		{
			text_vec[text_idx]->SetText(scripts[i]);
			text_vec[text_idx]->SetOffset(script_offset + char_interval * char_pos);
			text_vec[text_idx]->SetActive(true);
			text_idx++;
		}
		if (char_pos.x < line_length)
		{
			char_pos.x++;
		}
		else
		{
			char_pos.x = 0;
			char_pos.y += 1;
		}
	}
	for (int i = text_idx; i < text_vec.size(); i++)
	{
		text_vec[i]->SetActive(false);
	}
}
