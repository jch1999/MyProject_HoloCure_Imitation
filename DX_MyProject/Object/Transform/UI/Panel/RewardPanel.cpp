#include "framework.h"

RewardPanel::RewardPanel()
	:increaseSpd(100.0f),playTime(0.0f)
{
	popUp = new ImageArea(new Frame(L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png"
		, 4.0f, 790.0f, 208.0f, 240.0f));
	popUp->SetSize(Vector2(208.0f, 240.0f));
	popUp->SetScale(Vector2(1.7f, 1.7f));
	popUp->SetTarget(this);
	popUp->SetOffset(Vector2(0.0f, -WIN_CENTER_Y * 0.1f));
	popUp->SetState(UI_STATE::ACTIVE);
	child_list.push_back(popUp);

	// box 
	anim = new RewardBoxAnim();
	anim->SetTarget(popUp);
	anim->SetOffset(Vector2(0.0f, 25.0f));
	anim->SetScale(Vector2(1.3f, 1.3f));
	anim->SetAnimState(RewardBoxAnim::BOX_STATE::FALL);
	child_list.push_back(anim);

	spotLight = new ImageArea(new Frame(L"Textures/Item/PC Computer - HoloCure - Save the Fans - Holozon Box.png"
		, 251.0f, 52.0f, 262.0f, 360.0f));
	spotLight->SetState(UI_STATE::ACTIVE);
	spotLight->SetSize(Vector2(262.0f, 360.0f));
	spotLight->SetTarget(popUp);
	spotLight->SetOffset(Vector2(0.0f, -20.0f));
	spotLight->SetColor(Float4(1.0f, 1.0f, 1.0f, 0.8f));
	child_list.push_back(spotLight);
	
	openText = new TextPrinter();
	openText->SetTarget(popUp);
	openText->SetOffset(Vector2(-80.0f, 175.0f));
	openText->SetTextInfo(Vector2(0.3f, 0.3f), Vector2(12.0f, 20.0f));
	openText->SetText("Enter to Open!");
	openText->SetActive(false);
	child_list.push_back(openText);

	lEffect = new LightEffect();
	lEffect->SetTarget(anim);
	lEffect->SetOffset(Vector2(0.0f, 10.0f));
	lEffect->SetActive(false);
	lEffect->SetScale(Vector2(2.0f, 2.0f));
	lEffect->SetState(UI_STATE::IDLE);
	lEffect->SetDist(70.0f);
	child_list.push_back(lEffect);

	// coin
	coinImg = new ImageArea(new Frame(L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Item Icons_rm_bg.png"
		, 200.0f, 322.0f, 15.0f, 15.0f));
	coinImg->SetTarget(popUp);
	coinImg->SetOffset(Vector2(-20.0f, -150.0f));
	coinImg->SetScale(Vector2(0.7f, 0.7f));
	coinImg->SetState(UI::UI_STATE::ACTIVE);
	child_list.push_back(coinImg);

	coinText = new TextPrinter();
	coinText->SetTarget(coinImg);
	coinText->SetOffset(Vector2(35.0f, 0.0f));
	coinText->SetTextInfo(Vector2(0.5f, 0.5f), Vector2(15.0f, 20.0f));
	child_list.push_back(coinText);

	// Skill
	icon = new SkillIcon();
	icon->SetTarget(popUp);
	icon->SetOffset(Vector2(0.0f, -15.0f));
	icon->SetScale(Vector2(1.3f, 1.3f));
	icon->SetID(UI_ID::SKILL_ICON);
	icon->SetActive(false);
	child_list.push_back(icon);

	selector = new SkillSelector();
	selector->SetTarget(popUp);
	selector->SetOffset(Vector2(0.0f, popUp->GetSize().y*popUp->GetScale().y*0.75f));
	selector->SetScale(Vector2(1.5f, 1.5f));
	selector->SetIconOffset(Vector2(-245.0f, 5.0f));
	selector->SetNameTOffset(Vector2(-260.0f, -40.0f));
	selector->SetScriptTOffset(Vector2(-210.0f, -10.0f));
	selector->SetClipIdx(1);
	selector->SetActive(false);
	child_list.push_back(selector);
	
	// select btn
	getBtn = new Button();
	getBtn->SetTarget(this);
	getBtn->SetOffset(Vector2(WIN_CENTER_X * 0.5f, -WIN_START_Y * 0.35f));
	getBtn->SetSize(Vector2(110.0f,50.0f));
	getBtn->SetScale(Vector2(1.3f, 1.3f));
	getBtn->SetClipIdx(0);
	getBtn->SetState(UI_STATE::IDLE);
	getBtn->GetBtnText()->SetTextInfo(Vector2(0.3f, 0.3f), Vector2(12.0f, 20.0f));
	getBtn->GetBtnText()->SetText("Get");
	getBtn->GetBtnText()->AddOffset(Vector2(-15.0f, 0.0f));
	getBtn->SetActive(false);
	child_list.push_back(getBtn);

	dropBtn = new Button();
	dropBtn->SetTarget(this);
	dropBtn->SetOffset(Vector2(WIN_CENTER_X * 0.5f, WIN_START_Y * 0.35f));
	dropBtn->SetSize(Vector2(110.0f, 50.0f));
	dropBtn->SetScale(Vector2(1.3f, 1.3f));
	dropBtn->SetClipIdx(0);
	dropBtn->SetState(UI_STATE::IDLE);
	dropBtn->GetBtnText()->SetTextInfo(Vector2(0.3f, 0.3f), Vector2(12.0f, 20.0f));
	dropBtn->GetBtnText()->AddOffset(Vector2(-15.0f, 0.0f));
	dropBtn->GetBtnText()->SetText("Drop");
	dropBtn->SetActive(false);
	child_list.push_back(dropBtn);

	id = UI_ID::REWARD_PANEL;
	type = UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(WIN_WIDTH, WIN_HEIGHT);
	ui_scale = Vector2(1, 1);
	offset = WIN_CENTER;
	SetActive(false);
}

RewardPanel::~RewardPanel()
{
}

void RewardPanel::Update()
{
	if (!is_active)return;

	switch (anim->boxState)
	{
	case RewardBoxAnim::BOX_STATE::FALL:
	{
		if (anim->isAnimEnd())
		{
			anim->SetAnimState(RewardBoxAnim::BOX_STATE::CLOSED);
			openText->SetActive(true);
		}
	}
		break;
	case RewardBoxAnim::BOX_STATE::CLOSED:
	{
		if (KEY_CON->Down(VK_RETURN))
		{
			anim->SetAnimState(RewardBoxAnim::BOX_STATE::BOUNCING);
			ItemSpawner::Get()->nowCoinValue += targetCoinValue;
			spotLight->SetActive(false);
			openText->SetActive(false);
		}
	}
		break;
	case RewardBoxAnim::BOX_STATE::BOUNCING:
	{
		playTime += DELTA;
		if (playTime >= 2.0f && anim->isAnimEnd())
		{
			anim->SetAnimState(RewardBoxAnim::BOX_STATE::OPENING);
			anim->SetOffset(Vector2(0.0f, -50.0f));
			selector->SetSkillID(SkillManager::Get()->GetLevelUpSkillID());
			icon->SetSkillID(selector->GetSkillID());
			playTime = 0.0f;
		}

		if (coinValue < targetCoinValue)
			coinValue += increaseSpd * DELTA;
		else
			coinValue = targetCoinValue;

		coinText->SetText(to_string((int)coinValue));
	}
		break;
	case RewardBoxAnim::BOX_STATE::OPENING:
	{
		if (anim->isAnimEnd())
		{
			anim->SetAnimState(RewardBoxAnim::BOX_STATE::OPEN);
		}
		else if(playTime<0.65f)
		{
			playTime += DELTA;
			if (playTime >= 0.65f)
			{
				selector->SetActive(true);
				icon->SetActive(true);
				getBtn->SetActive(true);
				dropBtn->SetActive(true);
				lEffect->SetState(UI_STATE::ACTIVE);
			}
		}

		if(coinValue < targetCoinValue)
			coinValue += increaseSpd * DELTA;
		else
			coinValue = targetCoinValue;

		coinText->SetText(to_string((int)coinValue));
	}
		break;
	case RewardBoxAnim::BOX_STATE::OPEN:
	{
		anim->SetSize(Vector2(160.0f, 90.0f));
		coinValue = targetCoinValue;
		coinText->SetText(to_string((int)coinValue));
		// Ã¢´Ý±â
		if (KEY_CON->Down(VK_RETURN))
		{
			switch (selectIdx)
			{
			case 0:
				SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)selector->GetSkillID())->LevelUp();
				break;
			default:
				break;
			}
			UIManager::Get()->isReward = false;
			UIManager::Get()->nowPanel = nullptr;
			nowBox->SetState(Item::ITEM_STATE::USED);
			nowBox = nullptr;
			isPause = false;
			SetActive(false);
		}
		else if (KEY_CON->Down(VK_UP))
		{
			selectIdx++;
			selectIdx %= 2;
		}
		else if (KEY_CON->Down(VK_DOWN))
		{
			selectIdx--;
			if (selectIdx < 0)selectIdx = 1;
		}

		switch (selectIdx)
		{
			case 0:
			{
				getBtn->SetState(UI_STATE::ACTIVE);
				dropBtn->SetState(UI_STATE::IDLE);
			}
				break;
			case 1:
			{
				getBtn->SetState(UI_STATE::IDLE);
				dropBtn->SetState(UI_STATE::ACTIVE);
			}
				break;
			default:
				break;
		}

	}
		break;
	default:
		break;
	}

	if(target!=nullptr)
		pos = target->pos + offset;

	WorldUpdate();

	for (auto c : child_list)
		c->Update();
}

void RewardPanel::Render()
{
	if (!is_active)return;

	for (auto c : child_list)
		c->Render();
}

void RewardPanel::PostRender()
{
	if (!is_active)return;
}

void RewardPanel::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void RewardPanel::SetID(UI::UI_ID id)
{
	this->id = id;
}

void RewardPanel::SetActive(bool active)
{
	this->is_active = active;
	coinValue = 0.0f;
	targetCoinValue = (float)Random::Get()->GetRandomInt(ItemSpawner::Get()->coinValue * 30, ItemSpawner::Get()->coinValue * 50);
	coinText->SetText("0");

	anim->SetAnimState(RewardBoxAnim::BOX_STATE::FALL);
	anim->SetOffset(Vector2(0.0f, 25.0f));
	for (auto c : child_list)
		c->SetActive(active);

	openText->SetActive(false);
	lEffect->SetState(UI_STATE::IDLE);
	selector->SetActive(false);
	icon->SetActive(false);
	getBtn->SetActive(false);
	dropBtn->SetActive(false);
	playTime = 0.0f;
}
