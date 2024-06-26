#include "framework.h"

EnhancePanel::EnhancePanel()
	: selectIdx(0)
	,moveRot(0.0f),iconMoveSpd(300.0f)
	,targetPlayTime(2.0f),targetMoveTime(0.1f)
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
	enhanceRateText->SetOffset(Vector2(WIN_CENTER_X * 0.2f, WIN_CENTER_Y * 0.5f));
	enhanceRateText->SetState(UI::UI_STATE::IDLE);
	enhanceRateText->SetTextInfo(Vector2(0.3f, 0.3f), Vector2(10.0f, 20.0f));
	enhanceRateText->SetActive(false);
	child_list.push_back(enhanceRateText);

	popUp=new ImageArea(new Frame(L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png"
		, 4.0f, 790.0f, 208.0f, 240.0f));
	popUp->SetSize(Vector2(208.0f, 240.0f));
	popUp->SetScale(Vector2(1.7f, 1.7f));
	popUp->SetTarget(this);
	popUp->SetOffset(Vector2(0.0f, -WIN_CENTER_Y * 0.2f));
	popUp->SetState(UI_STATE::IDLE);
	child_list.push_back(popUp);

	icon = new SkillIcon();
	icon->SetScale(Vector2(1.5f, 1.5f));
	icon->SetID(UI_ID::SKILL_ICON);
	icon->SetActive(false);
	child_list.push_back(icon);

	btn = new Button();
	btn->SetTarget(this);
	btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
	btn->SetScale(Vector2(1.5f, 1.5f));
	btn->SetState(UI::UI_STATE::IDLE);
	btn->GetBtnText()->SetText("UPGRADE");
	btn->GetBtnText()->SetOffset(Vector2(-35.0f, 0.0f));
	child_list.push_back(btn);
	
	coinImg = new ImageArea(new Frame(L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Item Icons_rm_bg.png"
		, 200.0f, 322.0f, 15.0f, 15.0f));
	coinImg->SetTarget(btn);
	coinImg->SetOffset(Vector2(-40.0f, -2.0f));
	coinImg->SetScale(Vector2(0.7f, 0.7f));
	coinImg->SetState(UI::UI_STATE::IDLE);
	child_list.push_back(coinImg);

	enhanceResultText = new TextPrinter();
	enhanceResultText->SetActive(false);
	enhanceResultText->SetTarget(popUp);
	enhanceResultText->SetOffset(Vector2(-80.0f, -150.0f));
	child_list.push_back(enhanceResultText);
	
	iconOffset = Vector2(0.0f, 0.0f);

	cEffect = new ChargeEffect();
	cEffect->SetTarget(popUp);
	cEffect->SetOffset(Vector2(0.0f, 0.0f));
	cEffect->SetActive(false);
	cEffect->SetScale(Vector2(2.0f, 2.0f));
	cEffect->SetState(UI_STATE::IDLE);
	child_list.push_back(cEffect);

	sEffect = new LightEffect();
	sEffect->SetTarget(icon);
	sEffect->SetOffset(Vector2(0.0f, 0.0f));
	sEffect->SetActive(false);
	sEffect->SetScale(Vector2(2.0f, 2.0f));
	sEffect->SetState(UI_STATE::IDLE);
	sEffect->SetDist(70.0f);
	child_list.push_back(sEffect);

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

	switch (enhance_state)
	{
	case EnhancePanel::ENHANCE_STATE::START:
		ChoseSkill();
		break;
	case EnhancePanel::ENHANCE_STATE::ENHANCING:
		PlayEnhancing();
		break;
	case EnhancePanel::ENHANCE_STATE::END:
		EnhanceEnd();
		break;
	default:
		break;
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
	sEffect->PostRender();
}

void EnhancePanel::SetActive(bool active)
{
	this->is_active = active;
	selectIdx = 0;
	
	if (active == true)
	{
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
		selector->SetTarget(this);
		selector->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.25f));

		btn->SetTarget(this);
		btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
		btn->SetScale(Vector2(1.5f, 1.5f));
		btn->SetState(UI::UI_STATE::IDLE);
		btn->GetBtnText()->SetText("UPGRADE");
		btn->GetBtnText()->SetOffset(Vector2(-35.0f, 0.0f));

		for (auto c : child_list)
			c->SetActive(active);

		// popUp 관련
		enhanceRateText->SetActive(false);
		enhanceResultText->SetActive(false);
		icon->SetActive(false);

		coinImg->SetState(UI_STATE::IDLE);
		popUp->SetState(UI_STATE::IDLE);
		enhance_state = ENHANCE_STATE::START;
	}
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
					if (round(nowSkill->GetEnhanceCost()) <= round(ItemSpawner::Get()->nowCoinValue))
					{
						enhanceRateText->SetText("Success Rate : " + to_string(nowSkill->GetEnhanceRate()) + "%");
					}
					else
					{
						enhanceRateText->SetText("Not Enought HoloCoin!");
					}
					coinImg->SetState(UI_STATE::ACTIVE);
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
				&&round(ItemSpawner::Get()->nowCoinValue)>=round(nowSkill->GetEnhanceCost()))
			{
				if (nowSkill->GetLevelUpAble())
				{
					nowSkill->Enhance();
					selected = false;
					usedAnvil->SetState(Item::ITEM_STATE::USED);
					usedAnvil = nullptr;
					isPause = false;
					UIManager::Get()->nowPanel = nullptr;
					UIManager::Get()->isEnhance = false;
					SetActive(false);
				}
				else
				{
					isEnhancing = true;
					enhanceRateText->SetActive(false);
					icon->SetActive(true);
					icon->SetSkillID(skillIconList[selectIdx / 6][selectIdx % 6]->GetSkillID());
					icon->pos = popUp->pos;
					popUp->SetState(UI_STATE::ACTIVE);
					btn->SetActive(false);
					coinImg->SetState(UI_STATE::IDLE);
					selector->SetActive(false);
					cEffect->SetActive(true);
					cEffect->SetState(UI_STATE::ACTIVE);

					playTime = 0.0f;
					moveTime = 0.0f;
					moveRot = 0.0f;
					isReturning = false;
					enhance_state = ENHANCE_STATE::ENHANCING;
				}
			}
		}
		// 스킬 재 선택
		else if (KEY_CON->Down(VK_ESCAPE) || KEY_CON->Down(VK_BACK))
		{
			selected = false;

			enhanceRateText->SetActive(false);
			coinImg->SetState(UI_STATE::IDLE);
			btn->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.55f));
			btn->SetScale(Vector2(1.5f, 1.5f));
			btn->GetBtnText()->SetText("UPGRADE");
			btn->GetBtnText()->AddOffset(Vector2(90.0f, 0.0f));
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == selectIdx / 6 && j == selectIdx % 6)
			{
				selector->SetSkillID(skillIconList[i][j]->GetSkillID());
				skillIconList[i][j]->GetFrame()->SetClipIdx(5);
				if (skillIconList[i][j]->GetSkillID() == -1 || !SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillIconList[i][j]->GetSkillID())->GetEnhanceAble())
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
}

void EnhancePanel::PlayEnhancing()
{
	playTime += DELTA;
	moveTime += DELTA;
	if (playTime < targetPlayTime)
	{
		if (moveTime >= targetMoveTime)
		{
			if (isReturning)
			{
				isReturning = false;
				moveRot += 30.0f;
				icon->pos = popUp->pos + iconOffset;
			}
			else
				isReturning = true;
			moveTime -= 0.1f;
		}
		else
		{
			if (isReturning)
			{
				icon->pos = icon->pos - Vector2(cosf(moveRot), sinf(moveRot)) * iconMoveSpd * DELTA;

			}
			else
			{
				icon->pos = icon->pos + Vector2(cosf(moveRot), sinf(moveRot)) * iconMoveSpd * DELTA;
			}
		}
	}
	else
	{
		bool succed = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)icon->GetSkillID())->Enhance(); 
		icon->pos = popUp->pos + iconOffset;
		enhanceResultText->SetActive(true);
		enhanceResultText->SetTextInfo(Vector2(1.0f, 1.0f), Vector2(30.0f, 12.0f));
		if (succed)
		{
			enhanceResultText->SetOffset(Vector2(-85.0f, -150.0f));
			enhanceResultText->SetText("SUCCESS");
			sEffect->SetActive(true);
			sEffect->SetState(UI_STATE::ACTIVE);
		}
		else
		{
			enhanceResultText->SetOffset(Vector2(-65.0f, -150.0f));
			enhanceResultText->SetText("FAILED");
		}
		selected = false;
		usedAnvil->SetState(Item::ITEM_STATE::USED);
		usedAnvil = nullptr;
		enhance_state = ENHANCE_STATE::END;
		cEffect->SetState(UI_STATE::IDLE);
		cEffect->SetActive(false);
		// btn 재활성
		// text End
		btn->SetActive(true);
		btn->SetTarget(popUp);
		btn->SetScale(Vector2(1.0f, 1.5f));
		btn->SetOffset(Vector2(0.0f, WIN_CENTER_Y * 0.4f));
		btn->SetState(UI_STATE::ACTIVE);
		btn->GetBtnText()->SetText("OK");
		btn->GetBtnText()->AddOffset(Vector2(120.0f, 0.0f));
		// Selector 재활성
		// skill name + enhance level
		// skill script = enhace damage difference
		selector->SetActive(true);
		selector->SetTarget(popUp);
		selector->SetOffset(Vector2(0.0f, WIN_CENTER_Y * 0.75f));
		selector->SetSkillID(icon->GetSkillID());
		Skill* skill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)icon->GetSkillID());
		string name = skill->GetSkillName() + " +" + to_string(skill->GetEnhanceLevel());
		// 데미지 소수점 출력 자릿수를 2자리까지로 제한
		string beforeDmg = to_string(skill->GetEnhanceDamge() - ItemSpawner::Get()->enhanceDmg);
		string nowDmg = to_string(skill->GetEnhanceDamge());
		string script = "Enhance Damage: " + beforeDmg.substr(0, beforeDmg.find('.') + 2 + 1) + "  >>  "
			+ nowDmg.substr(0, nowDmg.find('.') + 2 + 1);
		selector->SetText(name, script);
	}
}

void EnhancePanel::EnhanceEnd()
{
	if (KEY_CON->Down(VK_RETURN))
	{
		sEffect->SetState(UI_STATE::IDLE);
		sEffect->SetActive(false);
		isPause = false;
		UIManager::Get()->nowPanel = nullptr;
		UIManager::Get()->isEnhance = false;
		SetActive(false);
	}
}
