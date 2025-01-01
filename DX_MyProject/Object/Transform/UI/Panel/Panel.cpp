#include "framework.h"

Panel::Panel(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
	, selectIdx(0)
{
	player_full_icon = new PlayerIcon();
	player_full_icon->SetID(UI_ID::PLAYER_FULL_ICON);
	player_full_icon->SetTarget(this);
	player_full_icon->SetScale(Vector2(3.0f, 3.0f));
	player_full_icon->SetOffset(Vector2(-WIN_CENTER_X * 0.65f, WIN_CENTER_Y * 0.15f));
	childList.push_back(player_full_icon);

	id = UI::UI_ID::LEVEL_UP_PANEL;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	is_active = false;
}

Panel::~Panel()
{
}

void Panel::Update()
{
	pos = target->pos + offset;
	WorldUpdate();

	for (auto ui : childList)
		ui->Update();
}

void Panel::Render()
{
	if (!is_active)return;


	for (auto ui : childList)
		ui->Render();
}

void Panel::PostRender()
{
}

void Panel::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void Panel::SetID(UI::UI_ID id)
{
	this->id = id;
}
