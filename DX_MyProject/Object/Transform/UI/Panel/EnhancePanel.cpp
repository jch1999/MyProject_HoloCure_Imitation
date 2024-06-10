#include "framework.h"

EnhancePanel::EnhancePanel()
	: select_idx(0)
{
	upgrade_text = new TextPrinter();
	upgrade_text->SetTarget(this);
	upgrade_text->SetOffset(Vector2(WIN_CENTER_X*0.2f, -WIN_CENTER_Y*0.5f));
	upgrade_text->SetCharScale(Vector2(1.0f, 1.0f));
	upgrade_text->SetCharInterval(Vector2(30.0f, 20.0f));
	upgrade_text->SetText("UPGRADE!");
	child_list.push_back(upgrade_text);

	Vector2 iconStartPos(WIN_CENTER_X*0.05f, -WIN_CENTER_Y*0.3f);
	Vector2 iconInterval(80.0f, 80.0f);
	skillIcon_list.resize(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			SkillIcon* icon = new SkillIcon();
			icon->SetTarget(this);
			icon->SetOffset(Vector2(iconStartPos.x + iconInterval.x * j,
				iconStartPos.y + iconInterval.y * i));
			icon->SetID(UI_ID::SKILL_ENHANCE_ICON);
			skillIcon_list[i].push_back(icon);
			child_list.push_back(icon);
		}
	}

	selector = new SkillSelector();
	selector->SetTarget(this);
	selector->SetOffset(Vector2(WIN_CENTER_X*0.35f, WIN_CENTER_Y * 0.25f));
	selector->SetScale(Vector2(1.5f, 1.5f));
	selector->SetIconOffset(Vector2(-245.0f, 5.0f));
	selector->SetNameTOffset(Vector2(-260.0f, -40.0f));
	selector->SetScriptTOffset(Vector2(-210.0f, -10.0f));
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

	ChoseSkill();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == select_idx / 6 && j == select_idx % 6)
			{
				selector->SetSkillID(skillIcon_list[i][j]->GetSkillID());
				(skillIcon_list[i][j]->GetFrame())->SetClipIdx(5);
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
	ImGui::Text("Type : %d, Idx : %d", select_idx/6, select_idx%6);
}

void EnhancePanel::SetActive(bool active)
{
	this->is_active = active;
	select_idx = 0;
	
	// weapon
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->weaponCnt)
		{
			int nowSkill_id = (int)(SkillManager::Get()->nowWeapon_list[i]->GetSkillID());
			skillIcon_list[0][i]->SetSkillID(nowSkill_id);
			if (SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkill_id)->GetEnhanceAble())
			{
				skillIcon_list[0][i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				skillIcon_list[0][i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.3f));
			}
		}
		else
		{
			skillIcon_list[0][i]->SetSkillID(-1);
		}
	}
	// buff
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->buffCnt)
		{
			int nowSkill_id = (int)(SkillManager::Get()->nowBuff_list[i]->GetSkillID());
			skillIcon_list[1][i]->SetSkillID(nowSkill_id);
			if (SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkill_id)->GetEnhanceAble())
			{
				skillIcon_list[1][i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				skillIcon_list[1][i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.3f));
			}
		}
		else
		{
			skillIcon_list[1][i]->SetSkillID(-1);
		}
	}

	selector->SetClipIdx(1);

	for (auto c : child_list)
		c->SetActive(active);
}

void EnhancePanel::ChoseSkill()
{
	if (!selected)
	{
		// 선택 항목 이동 입력
		if (KEY_CON->Down(VK_UP))
		{
			select_idx -= 6;
			if (select_idx < 0)
				select_idx += 12;
		}
		else if (KEY_CON->Down(VK_DOWN))
		{
			select_idx += 6;
			select_idx %= 12;
		}
		else if (KEY_CON->Down(VK_LEFT))
		{
			select_idx -= 1;
			if (select_idx < 0)
				select_idx = 11;
		}
		else if (KEY_CON->Down(VK_RIGHT))
		{
			select_idx += 1;
			select_idx %= 12;
		}
		// 현재 포커스 스킬 선택
		else if (KEY_CON->Down(VK_RETURN)) // Enter로 결정
		{
			int now_skillId = skillIcon_list[select_idx/6][select_idx%6]->GetSkillID();
			if (now_skillId != -1)
			{
				Skill* nowSkill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)now_skillId);
				if (nowSkill->GetEnhanceAble())
					selected = true;
			}
		}
		else if (KEY_CON->Down(VK_ESCAPE) || KEY_CON->Down(VK_BACK))
		{
			usedAnvil->SetState(Item::ITEM_STATE::IDLE);
			isPause = false;
			usedAnvil = nullptr;
			UIManager::Get()->nowPanel = nullptr;
			UIManager::Get()->isEnhance = false;
			SetActive(false);
		}
	}
	// 선택 확정 or 취소 입력
	else
	{
		if (KEY_CON->Down(VK_LEFT))
		{
			final_idx -= 1;
			if (final_idx < 0)final_idx = 1;
		}
		else if (KEY_CON->Down(VK_RIGHT))
		{
			final_idx += 1;
			final_idx %= 2;
		}
		// 모루 사용
		else if (KEY_CON->Down(VK_RETURN))
		{
			Skill* nowSkill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillIcon_list[select_idx/6][select_idx%6]->GetSkillID());
			if (nowSkill->GetLevelUpAble())
			{
				nowSkill->LevelUp();
			}
			else
			{
				nowSkill->Enhance();
			}
			selected = false;
			usedAnvil->SetState(Item::ITEM_STATE::USED);
			usedAnvil = nullptr;
			isPause = false;
			UIManager::Get()->nowPanel = nullptr;
			UIManager::Get()->isEnhance = false;
			SetActive(false);
		}
		// 스킬 재 선택
		else if (KEY_CON->Down(VK_ESCAPE) || KEY_CON->Down(VK_BACK))
		{
			selected = false;
		}
	}
}
