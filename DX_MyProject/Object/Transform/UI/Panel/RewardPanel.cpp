#include "framework.h"

RewardPanel::RewardPanel()
	:increaseSpd(100.0f)
{
	popUp = new ImageArea(new Frame(L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png"
		, 4.0f, 790.0f, 208.0f, 240.0f));
	popUp->SetSize(Vector2(208.0f, 240.0f));
	popUp->SetScale(Vector2(1.7f, 1.7f));
	popUp->SetTarget(this);
	popUp->SetOffset(Vector2(0.0f, -WIN_CENTER_Y * 0.2f));
	popUp->SetState(UI_STATE::ACTIVE);
	child_list.push_back(popUp);

	// box 
	anim = new RewardBoxAnim();
	anim->SetTarget(popUp);
	anim->SetOffset(Vector2());
	anim->SetScale(Vector2(1.5f, 1.5f));
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

	// coin
	coinImg = new ImageArea(new Frame(L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Item Icons_rm_bg.png"
		, 200.0f, 322.0f, 15.0f, 15.0f));
	coinImg->SetTarget(popUp);
	coinImg->SetOffset(Vector2(0.0f, -150.0f));
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
	icon->SetScale(Vector2(1.5f, 1.5f));
	icon->SetID(UI_ID::SKILL_ICON);
	icon->SetActive(false);
	child_list.push_back(icon);

	selector = new SkillSelector();
	selector->SetTarget(this);
	selector->SetOffset(Vector2(WIN_CENTER_X * 0.35f, WIN_CENTER_Y * 0.25f));
	selector->SetScale(Vector2(1.5f, 1.5f));
	selector->SetIconOffset(Vector2(-245.0f, 5.0f));
	selector->SetNameTOffset(Vector2(-260.0f, -40.0f));
	selector->SetScriptTOffset(Vector2(-210.0f, -10.0f));
	selector->SetActive(false);
	child_list.push_back(selector);

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
		anim->SetSize(Vector2(160.0f, 90.0f));
	}
		break;
	case RewardBoxAnim::BOX_STATE::CLOSED:
	{
		anim->SetSize(Vector2(160.0f, 90.0f));
		if (KEY_CON->Down(VK_RETURN))
		{
			anim->SetAnimState(RewardBoxAnim::BOX_STATE::BOUNCING);
			ItemSpawner::Get()->nowCoinValue += targetCoinValue;
			spotLight->SetActive(false);
		}
	}
		break;
	case RewardBoxAnim::BOX_STATE::BOUNCING:
	case RewardBoxAnim::BOX_STATE::OPENING:
	{
		anim->SetSize(Vector2(160.0f, 90.0f));
		if (coinValue < targetCoinValue)
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
	for (auto c : child_list)
		c->SetActive(active);

	selector->SetActive(false);
}
