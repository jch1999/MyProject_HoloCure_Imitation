#include "framework.h"

LevelUpPanel::LevelUpPanel()
{
	levelUp_text = new Text();
	levelUp_text->SetID(UI_ID::LEVEL_UP_TEXT);
	levelUp_text->SetTarget(this);
	levelUp_text->SetSize(Vector2(94.0f, 20.0f));
	levelUp_text->SetScale(Vector2(2.0f, 2.0f));
	levelUp_text->SetOffset(Vector2(-WIN_CENTER_X * 0.65f, -WIN_CENTER_Y * 0.45f));
	child_list.push_back(levelUp_text);

	player_full_icon = new Icon();
	player_full_icon->SetID(UI_ID::PLAYER_FULL_ICON);
	player_full_icon->SetTarget(this);
	player_full_icon->SetScale(Vector2(3.0f, 3.0f));
	player_full_icon->SetOffset(Vector2(-WIN_CENTER_X * 0.65f, WIN_CENTER_Y * 0.15f));
	child_list.push_back(player_full_icon);

	Vector2 selector_initOffset(WIN_CENTER_X * 0.5f, -WIN_CENTER_Y * 0.4f);
	for (int i = 0; i < 4; i++)
	{
		SkillSelector* selector = new SkillSelector();
		selector->SetTarget(this);
		selector->SetOffset(selector_initOffset);
		selector->SetScale(Vector2(1.3f, 1.3f));

		skill_selectors.push_back(selector);
		child_list.push_back(selector);
	}
	id = UI::UI_ID::LEVEL_UP_PANEL;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(WIN_WIDTH, WIN_HEIGHT);
	ui_scale = Vector2(1, 1);
	offset = WIN_CENTER;
	is_active = false;
}

LevelUpPanel::~LevelUpPanel()
{
}

void LevelUpPanel::Update()
{
	if (!is_active)return;

	if (KEY_CON->Down('C'))
	{
		isPause = false;
		SetActive(false);
		UIManager::Get()->nowPanel = nullptr;
	}
	pos = target->pos + offset;
	WorldUpdate();

	for (auto ui : child_list)
		ui->Update();
}

void LevelUpPanel::Render()
{
	if(!is_active)return;


	for (auto ui : child_list)
		ui->Render();
}

void LevelUpPanel::PostRender()
{
}

void LevelUpPanel::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void LevelUpPanel::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LevelUpPanel::SetActive(bool active)
{
	this->is_active = active;
	for (auto ui : child_list)
		ui->SetActive(active);
}
