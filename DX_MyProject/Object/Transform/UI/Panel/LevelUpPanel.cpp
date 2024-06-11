#include "framework.h"

LevelUpPanel::LevelUpPanel()
{
	levelUpText = new LevelText();
	levelUpText->SetID(UI_ID::LEVEL_TEXT);
	levelUpText->SetClipIdx(0);
	levelUpText->SetTarget(this);
	levelUpText->SetSize(Vector2(94.0f, 20.0f));
	levelUpText->SetScale(Vector2(2.0f, 2.0f));
	levelUpText->SetOffset(Vector2(-WIN_CENTER_X * 0.65f, -WIN_CENTER_Y * 0.45f));
	child_list.push_back(levelUpText);

	Vector2 selector_initOffset(WIN_CENTER_X * 0.5f, -WIN_CENTER_Y * 0.4f);
	Vector2 interval(0.0f, 100.0f);
	for (int i = 0; i < 4; i++)
	{
		SkillSelector* selector = new SkillSelector();
		selector->SetTarget(this);
		selector->SetOffset(selector_initOffset + interval * i);
		selector->SetScale(Vector2(1.3f, 1.3f));
		selector->SetSkillID(1);

		skillSelectors.push_back(selector);
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
		if (selectIdx == 0)
			selectIdx = 3;
		else
			selectIdx--;
	}
	if (KEY_CON->Down(VK_DOWN))
	{
		selectIdx++;
		selectIdx %= 4;
	}

	for (int i = 0; i < 4; i++)
	{
		if (i == selectIdx)
		{
			skillSelectors[i]->SetClipIdx(1);
		}
		else
		{
			skillSelectors[i]->SetClipIdx(0);
		}
	}
	
	if (KEY_CON->Down(VK_RETURN))
	{
		// selector에서 id를 가져와 해당 아이디의 스킬의 level을 상승
		SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)(skillSelectors[selectIdx]->GetSkillID()))->LevelUp();
		isPause = false;
		UIManager::Get()->nowPanel = nullptr;
		UIManager::Get()->levelUpCnt--;
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
		skillSelectors[i]->PostRender();
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
	vector<int> selectedList;
	for (int i = 0; i < 4; i++)
	{
		int cnt = 0; // 중복 횟수
		while (cnt < 3) // 최대 3번 까지 중복 검사
		{
			bool equal = false;
			int selectedId = SkillManager::Get()->GetLevelUpSkillID();
			for (int j = 0; j < selectedList.size(); j++)
			{
				if (selectedList[j] == selectedId)
				{
					equal = true;
					break;
				}
			}
			if (equal)
				cnt++;
			else
			{
				selectedList.push_back(selectedId);
				break;
			}
		}
		if (cnt == 3) // 3번 중복되면 extra에서 차출
		{
			selectedList.push_back(SkillManager::Get()->GetLevelUpSkillID_E());
		}
	}
	for (int i = 0; i < 4; i++)
	{
		skillSelectors[i]->SetSkillID(selectedList[i]);
	}
}
