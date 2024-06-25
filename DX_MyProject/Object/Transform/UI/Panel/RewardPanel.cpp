#include "framework.h"

RewardPanel::RewardPanel()
{
	popUp = new ImageArea(new Frame(L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png"
		, 4.0f, 790.0f, 208.0f, 240.0f));
	popUp->SetSize(Vector2(208.0f, 240.0f));
	popUp->SetScale(Vector2(1.7f, 1.7f));
	popUp->SetTarget(this);
	popUp->SetOffset(Vector2(0.0f, -WIN_CENTER_Y * 0.2f));
	popUp->SetState(UI_STATE::ACTIVE);
	child_list.push_back(popUp);

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

	if (anim->boxState == RewardBoxAnim::BOX_STATE::CLOSED)
	{
		if (KEY_CON->Down(VK_RETURN))
		{
			anim->SetAnimState(RewardBoxAnim::BOX_STATE::BOUNCING);
		}
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
	anim->SetAnimState(RewardBoxAnim::BOX_STATE::FALL);
	for (auto c : child_list)
		c->SetActive(active);
}
