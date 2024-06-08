#include "framework.h"

EnhancePanel::EnhancePanel()
	:select_type(0),select_idx(0)
{
	upgrade_text = new TextPrinter();
	upgrade_text->SetTarget(this);
	upgrade_text->SetOffset(Vector2(50.0f, 50.0f));
	upgrade_text->SetText("UPGRADE!");
	upgrade_text->SetCharScale(Vector2(0.5f, 0.5f));
	upgrade_text->SetCharInterval(Vector2(10.0f, 20.0f));
	upgrade_text->SetActive(true);
	child_list.push_back(upgrade_text);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			SkillIcon* icon = new SkillIcon();
			icon->SetTarget(this);
			icon->SetOffset(Vector2(50.0f * j, i * 50.0f));
			icon->SetID(UI_ID::SKILL_ENHANCE_ICON);
			skillIcon_list[i].push_back(icon);
			child_list.push_back(icon);
		}
	}

	selector = new SkillSelector();
	selector->SetTarget(this);
	selector->SetOffset(Vector2());
	child_list.push_back(selector);

	id = UI::UI_ID::ENHANCE_PANEL;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(WIN_WIDTH, WIN_HEIGHT);
	ui_scale = Vector2(1, 1);
	offset = WIN_CENTER;
	is_active = false;
}

EnhancePanel::~EnhancePanel()
{
}

void EnhancePanel::Update()
{
	if (!is_active)return;
	
	if (!selected)
	{
		// 선택 항목 이동 입력
		if (KEY_CON->Down(VK_UP))
		{
			select_type -= 1;
			select_type %= 2;
		}
		else if (KEY_CON->Down(VK_DOWN))
		{

			select_type += 1;
			select_type %= 2;
		}
		else if (KEY_CON->Down(VK_LEFT))
		{
			select_idx -= 1;
			select_idx %= 6;
		}
		else if (KEY_CON->Down(VK_RIGHT))
		{

			select_idx += 1;
			select_idx %= 6;
		}
		// 현재 포커스 스킬 선택
		else if (KEY_CON->Down(VK_RETURN)) // Enter로 결정
		{
			Skill* nowSkill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillIcon_list[select_type][select_idx]->GetSkillID());
			if(nowSkill->GetEnhanceAble())
				selected = true;
		}
		else if (KEY_CON->Down(VK_ESCAPE)|| KEY_CON->Down(VK_BACK))
		{
			usedAnvil->SetState(Item::ITEM_STATE::IDLE);
			UIManager::Get()->nowPanel = nullptr;
			isPause = false;
		}
	}
	// 선택 확정 or 취소 입력
	else
	{
		if (KEY_CON->Down(VK_LEFT))
		{
			final_idx -= 1;
			final_idx %= 2;
		}
		else if (KEY_CON->Down(VK_RIGHT))
		{

			final_idx += 1;
			final_idx %= 2;
		}
		// 모루 사용
		else if (KEY_CON->Down(VK_RETURN))
		{
			Skill* nowSkill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillIcon_list[select_type][select_idx]->GetSkillID());
			if (nowSkill->GetLevelUpAble())
			{
				nowSkill->LevelUp();
			}
			else
			{
				nowSkill->Enhance();
			}
			usedAnvil->SetState(Item::ITEM_STATE::USED);
			usedAnvil = nullptr;
		}
		// 스킬 재 선택
		else if (KEY_CON->Down(VK_ESCAPE) || KEY_CON->Down(VK_BACK))
		{
			selected = false;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == select_type && j == select_idx)
			{
				(skillIcon_list[i][j]->GetFrame())->SetClipIdx(5);
				selector->SetSkillID(skillIcon_list[i][j]->GetSkillID());
			}
			else
				(skillIcon_list[i][j]->GetFrame())->SetClipIdx(4);
		}
	}

	pos = target->pos + offset;
	WorldUpdate();

	for (auto c : child_list)
		c->Update();
}

void EnhancePanel::Render()
{
	if (!is_active)return;

	for (auto c : child_list)
		c->Render();
}

void EnhancePanel::PostRender()
{
}

void EnhancePanel::SetActive(bool active)
{
	select_type = 0;
	select_idx = 0;
	
	// weapon
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->weaponCnt)
		{
			int nowSkill_id = (int)SkillManager::Get()->nowWeapon_list[i];
			skillIcon_list[0][i]->SetSkillID(nowSkill_id);
			if (SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkill_id)->GetEnhanceAble())
			{
				skillIcon_list[0][i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				skillIcon_list[0][i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.8f));
			}
		}
		else
		{
			skillIcon_list[0][i]->SetSkillID(-1);
		}
		skillIcon_list[0][i]->SetActive(true);
		
	}
	// buff
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->buffCnt)
		{
			int nowSkill_id = (int)SkillManager::Get()->nowBuff_list[i];
			skillIcon_list[1][i]->SetSkillID(nowSkill_id);
			if (SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkill_id)->GetEnhanceAble())
			{
				skillIcon_list[1][i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				skillIcon_list[1][i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.8f));
			}
		}
		else
		{
			skillIcon_list[1][i]->SetSkillID(-1);
		}
		skillIcon_list[1][i]->SetActive(true);

	}

	for (auto c : child_list)
		c->SetActive(true);
}
