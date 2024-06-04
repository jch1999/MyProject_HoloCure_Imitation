#include "framework.h"

Panel::Panel()
{
	player_full_icon = new PlayerIcon();
	player_full_icon->SetID(UI_ID::PLAYER_FULL_ICON);
	player_full_icon->SetTarget(this);
	player_full_icon->SetScale(Vector2(3.0f, 3.0f));
	player_full_icon->SetOffset(Vector2(-WIN_CENTER_X * 0.65f, WIN_CENTER_Y * 0.15f));
	child_list.push_back(player_full_icon);

	id = UI::UI_ID::LEVEL_UP_PANEL;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(WIN_WIDTH, WIN_HEIGHT);
	ui_scale = Vector2(1, 1);
	offset = WIN_CENTER;
	is_active = false;
}

Panel::~Panel()
{
}

void Panel::Update()
{
	pos = target->pos + offset;
	WorldUpdate();

	for (auto ui : child_list)
		ui->Update();
}

void Panel::Render()
{
	if (!is_active)return;


	for (auto ui : child_list)
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
