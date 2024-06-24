#include "framework.h"

RewardBoxAnim::RewardBoxAnim()
{
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Holozon Box.png";

	// Fall clip

	// Closed clip

	// Bouncing clip

	// Opening clip

	// Open clip

	id = UI_ID::IMAGE;
	type = UI_TYPE::IMAGE;
	state = UI_STATE::IDLE;
	boxState = BOX_STATE::FALL;
	SetActive(false);
}

RewardBoxAnim::~RewardBoxAnim()
{
}

void RewardBoxAnim::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	for (auto c : child_list)
		c->Update();
}

void RewardBoxAnim::Render()
{
	if (!is_active)return;

	clips[clip_idx]->Render();
	for (auto c : child_list)
		c->Update();
}

void RewardBoxAnim::PostRender()
{
}

void RewardBoxAnim::SetState(UI::UI_STATE state)
{
}

void RewardBoxAnim::SetID(UI::UI_ID id)
{
}
