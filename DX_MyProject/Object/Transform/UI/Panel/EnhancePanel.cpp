#include "framework.h"

EnhancePanel::EnhancePanel()
	:select_type(0),select_idx(0)
{
	upgrade_text = new TextPrinter();
	upgrade_text->SetTarget(this);
	upgrade_text->SetOffset(Vector2(50.0f, 50.0f));
	upgrade_text->SetText("UPGRADE!");
	upgrade_text->SetCharScale(Vector2(0.5f, 0.5f));
	upgrade_text->SetCharInterval(Vector2(10.0f, 20.0f));
	upgrade_text->SetActive(true);
	child_list.push_back(upgrade_text);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			SkillIcon* icon = new SkillIcon();
			icon->SetTarget(this);
			icon->SetOffset(Vector2());
			skillIcon_list[i].push_back(icon);
			child_list.push_back(icon);
		}
	}

	selector = new SkillSelector();
	selector->SetTarget(this);
	selector->SetOffset(Vector2());
	child_list.push_back(selector);

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
	
	if (KEY_CON->Down(VK_UP))
	{
		select_type -= 1;
		select_type %= 2;
	}
	if (KEY_CON->Down(VK_DOWN))
	{

		select_type += 1;
		select_type %= 2;
	}
	if (KEY_CON->Down(VK_LEFT))
	{
		select_idx -= 1;
		select_idx %= 6;
	}
	if (KEY_CON->Down(VK_RIGHT))
	{

		select_idx += 1;
		select_idx %= 6;
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
}

void EnhancePanel::SetActive(bool active)
{
	select_type = 0;
	select_idx = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->weaponCnt)
		{

		}
	}

	for (auto c : child_list)
		c->SetActive(true);
}
