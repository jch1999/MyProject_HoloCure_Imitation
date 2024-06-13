#include "framework.h"

EnhancePanel::EnhancePanel()
	: selectIdx(0)
{
	upgradeText = new TextPrinter();
	upgradeText->SetTarget(this);
	upgradeText->SetOffset(Vector2(WIN_CENTER_X*0.2f, -WIN_CENTER_Y*0.5f));
	upgradeText->SetTextInfo(Vector2(1.0f, 1.0f), Vector2(30.0f, 20.0f));
	upgradeText->SetText("UPGRADE!");
	child_list.push_back(upgradeText);

	Vector2 iconStartPos(WIN_CENTER_X*0.05f, -WIN_CENTER_Y*0.3f);
	Vector2 iconInterval(80.0f, 80.0f);
	skillIconList.resize(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			SkillIcon* icon = new SkillIcon();
			icon->SetTarget(this);
			icon->SetOffset(Vector2(iconStartPos.x + iconInterval.x * j,
				iconStartPos.y + iconInterval.y * i));
			icon->SetID(UI_ID::SKILL_ENHANCE_ICON);
			icon->GetFrame()->SetClipIdx(4);
			skillIconList[i].push_back(icon);
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

	enhanceRateText = new TextPrinter();
	enhanceRateText->SetTarget(this);
	enhanceRateText->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
	enhanceRateText->SetState(UI::UI_STATE::IDLE);
	enhanceRateText->SetActive(false);
	child_list.push_back(enhanceRateText);

	btn = new Button();
	btn->SetTarget(this);
	btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
	btn->SetScale(Vector2(1.5f, 1.5f));
	btn->SetState(UI::UI_STATE::IDLE);
	btn->GetBtnText()->SetText("UPGRADE");
	btn->GetBtnText()->SetOffset(Vector2(-35.0f, 0.0f));
	child_list.push_back(btn);

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
			if (i == selectIdx / 6 && j == selectIdx % 6)
			{
				selector->SetSkillID(skillIconList[i][j]->GetSkillID());
				skillIconList[i][j]->GetFrame()->SetClipIdx(5);
				if (skillIconList[i][j]->GetSkillID()==-1||!SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillIconList[i][j]->GetSkillID())->GetEnhanceAble())
				{
					btn->SetState(UI::UI_STATE::IDLE);
				}
				else
				{
					btn->SetState(UI::UI_STATE::ACTIVE);
				}
			}
			else
				skillIconList[i][j]->GetFrame()->SetClipIdx(4);
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
	ImGui::Text("Type : %d, Idx : %d", selectIdx/6, selectIdx%6);
}

void EnhancePanel::SetActive(bool active)
{
	this->is_active = active;
	selectIdx = 0;
	
	// weapon
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->weaponCnt)
		{
			int nowSkillId = (int)(SkillManager::Get()->nowWeapon_list[i]->GetSkillID());
			skillIconList[0][i]->SetSkillID(nowSkillId);
			if (SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkillId)->GetEnhanceAble())
			{
				skillIconList[0][i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				skillIconList[0][i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.3f));
			}
		}
		else
		{
			skillIconList[0][i]->SetSkillID(-1);
		}
	}
	// buff
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->buffCnt)
		{
			int nowSkill_id = (int)(SkillManager::Get()->nowBuff_list[i]->GetSkillID());
			skillIconList[1][i]->SetSkillID(nowSkill_id);
			if (SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkill_id)->GetEnhanceAble())
			{
				skillIconList[1][i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				skillIconList[1][i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.3f));
			}
		}
		else
		{
			skillIconList[1][i]->SetSkillID(-1);
		}
	}

	selector->SetClipIdx(1);
	
	btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
	btn->SetScale(Vector2(1.5f, 1.5f));
	btn->SetState(UI::UI_STATE::IDLE);
	btn->GetBtnText()->SetText("UPGRADE");
	btn->GetBtnText()->SetOffset(Vector2(-35.0f,0.0f));

	for (auto c : child_list)
		c->SetActive(active);

	enhanceRateText->SetActive(false);
}

void EnhancePanel::ChoseSkill()
{
	if (!selected)
	{
		// 선택 항목 이동 입력
		if (KEY_CON->Down(VK_UP))
		{
			selectIdx -= 6;
			if (selectIdx < 0)
				selectIdx += 12;
		}
		else if (KEY_CON->Down(VK_DOWN))
		{
			selectIdx += 6;
			selectIdx %= 12;
		}
		else if (KEY_CON->Down(VK_LEFT))
		{
			selectIdx -= 1;
			if (selectIdx < 0)
				selectIdx = 11;
		}
		else if (KEY_CON->Down(VK_RIGHT))
		{
			selectIdx += 1;
			selectIdx %= 12;
		}
		// 현재 포커스 스킬 선택
		else if (KEY_CON->Down(VK_RETURN)) // Enter로 결정
		{
			int nowSkillId = skillIconList[selectIdx/6][selectIdx%6]->GetSkillID();
			if (nowSkillId != -1)
			{
				Skill* nowSkill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)nowSkillId);
				if (nowSkill->GetEnhanceAble())
				{
					selected = true;
					btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.6f));
					btn->SetScale(Vector2(1.5f, 1.5f) * Vector2(2.0f, 1.0f));
					string str = "Cost :      " + to_string(nowSkill->GetEnhanceCost());
					
					for (int i = str.length(); i < 19; i++)
						str += " ";
					str += "UPGRADE";
					btn->GetBtnText()->SetText(str);
					btn->GetBtnText()->AddOffset(Vector2(-90.0f, 0.0f));

					enhanceRateText->SetActive(true);
					if (nowSkill->GetEnhanceCost() < ItemSpawner::Get()->nowCoinValue)
					{
						enhanceRateText->SetText("Success Rate : " + to_string(nowSkill->GetEnhanceRate()));
					}
					else
					{
						enhanceRateText->SetText("Not Enought HoloCoin!");
					}
				}
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
		// 모루 사용
		if (KEY_CON->Down(VK_RETURN))
		{
			Skill* nowSkill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillIconList[selectIdx/6][selectIdx%6]->GetSkillID());
			if (nowSkill->GetEnhanceAble()
				&&ItemSpawner::Get()->nowCoinValue>nowSkill->GetEnhanceCost())
			{
				selected = false;
				usedAnvil->SetState(Item::ITEM_STATE::USED);
				usedAnvil = nullptr;
				isPause = false;
				UIManager::Get()->nowPanel = nullptr;
				UIManager::Get()->isEnhance = false;
				SetActive(false);
			}
		}
		// 스킬 재 선택
		else if (KEY_CON->Down(VK_ESCAPE) || KEY_CON->Down(VK_BACK))
		{
			selected = false;

			btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
			btn->SetScale(Vector2(1.5f, 1.5f));
			btn->GetBtnText()->SetText("UPGRADE");
			btn->GetBtnText()->AddOffset(Vector2(90.0f, 0.0f));
		}
	}
}
