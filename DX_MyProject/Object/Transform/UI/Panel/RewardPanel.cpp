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
	anim->SetAnimState(RewardBoxAnim::BOX_STATE::FALL);
	child_list.push_back(anim);


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

}

void RewardPanel::Render()
{
	if (!is_active)return;
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
	
}
