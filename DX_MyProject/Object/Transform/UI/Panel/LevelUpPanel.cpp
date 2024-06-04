#include "framework.h"

LevelUpPanel::LevelUpPanel()
{
	levelUp_text = new LevelText();
	levelUp_text->SetID(UI_ID::LEVEL_TEXT);
	levelUp_text->SetClipIdx(0);
	levelUp_text->SetTarget(this);
	levelUp_text->SetSize(Vector2(94.0f, 20.0f));
	levelUp_text->SetScale(Vector2(2.0f, 2.0f));
	levelUp_text->SetOffset(Vector2(-WIN_CENTER_X * 0.65f, -WIN_CENTER_Y * 0.45f));
	child_list.push_back(levelUp_text);

	Vector2 selector_initOffset(WIN_CENTER_X * 0.5f, -WIN_CENTER_Y * 0.4f);
	Vector2 interval(0.0f, 100.0f);
	for (int i = 0; i < 4; i++)
	{
		SkillSelector* selector = new SkillSelector();
		selector->SetTarget(this);
		selector->SetOffset(selector_initOffset + interval * i);
		selector->SetScale(Vector2(1.3f, 1.3f));
		selector->SetSkillID(1);

		skill_selectors.push_back(selector);
		child_list.push_back(selector);
	}
	id = UI::UI_ID::LEVEL_UP_PANEL;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(WIN_WIDTH, WIN_HEIGHT);
	ui_scale = Vector2(1, 1);
	offset = WIN_CENTER;
	is_active = false;
}

LevelUpPanel::~LevelUpPanel()
{
}

void LevelUpPanel::Update()
{
	if (!is_active)return;

	if (KEY_CON->Down(VK_UP))
	{
		if (select_idx == 0)
			select_idx = 3;
		else
			select_idx--;
	}
	if (KEY_CON->Down(VK_DOWN))
	{
		select_idx++;
		select_idx %= 4;
	}

	for (int i = 0; i < 4; i++)
	{
		if (i == select_idx)
		{
			skill_selectors[i]->SetClipIdx(1);
		}
		else
		{
			skill_selectors[i]->SetClipIdx(0);
		}
	}
	
	if (KEY_CON->Down(VK_RETURN))
	{
		// selector에서 id를 가져와 해당 아이디의 스킬의 level을 상승
		SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)(skill_selectors[select_idx]->GetSkillID()))->LevelUp();
		isPause = false;
		UIManager::Get()->nowPanel = nullptr;
		UIManager::Get()->isLevelUp = false;
		SetActive(false);
		return;
	}

	

	Panel::Update();
}

void LevelUpPanel::Render()
{
	Panel::Render();
}

void LevelUpPanel::PostRender()
{
	for (int i = 0; i < 4; i++)
	{
		skill_selectors[i]->PostRender();
	}
}

void LevelUpPanel::SetActive(bool active)
{
	this->is_active = active;
	for (auto ui : child_list)
		ui->SetActive(active);
}

void LevelUpPanel::SetSkillSelector()
{
	vector<int> selected_list;
	for (int i = 0; i < 4; i++)
	{
		int cnt = 0; // 중복 횟수
		while (cnt < 3) // 최대 3번 까지 중복 검사
		{
			bool equal = false;
			int selected_id = SkillManager::Get()->GetLevelUpSkillID();
			for (int j = 0; j < selected_list.size(); j++)
			{
				if (selected_list[j] == selected_id)
				{
					equal = true;
					break;
				}
			}
			if (equal)
				cnt++;
			else
			{
				selected_list.push_back(selected_id);
				break;
			}
		}
		if (cnt == 3) // 3번 중복되면 extra에서 차출
		{
			selected_list.push_back(SkillManager::Get()->GetLevelUpSkillID_E());
		}
	}
	for (int i = 0; i < 4; i++)
	{
		skill_selectors[i]->SetSkillID(selected_list[i]);
	}
}
