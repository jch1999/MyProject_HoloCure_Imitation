#include "framework.h"

UIManager::UIManager()
{
	ui_list.push_back(new HPBar());
	ui_list.push_back(new HPBar());

	for (int i = 0; i < 100; i++)
	{
		ui_list.push_back(new DmgText());
	}
}

UIManager::~UIManager()
{
	for (auto ui : ui_list)
		delete ui;
}

void UIManager::Update()
{
	for (auto ui : ui_list)
	{
		ui->Update();
	}
}

void UIManager::Render()
{
	for (auto ui : ui_list)
		ui->Render();
}

void UIManager::PostRneder()
{
	for (auto ui : ui_list)
		ui->PostRender();
}

UI* UIManager::GenerateUI(UI::UI_ID id, Transform* t, Vector2 size, Vector2 offset)
{
	switch (id)
	{
	case UI::UI_ID::DMG_TEXT:
	case UI::UI_ID::CRT_DMG_TEXT:
	{
		UI* dmgText = new DmgText();
		dmgText->SetID(id);
		ui_list.push_back(dmgText);
	}
		break;
	case UI::UI_ID::HP_BAR:
	case UI::UI_ID::HP_BAR_BACK:
	{
		UI* hp = new HPBar();
		hp->SetID(id);
		hp->SetState(UI::UI_STATE::IDLE);
		ui_list.push_back(hp);
		return hp;
	}
	break;
	case UI::UI_ID::EXP_BAR:
		break;
	case UI::UI_ID::PlayerIcon:
		break;
	default:
		break;
	}
}

UI* UIManager::GetUI(UI::UI_ID id)
{
	UI* target = nullptr;
	UI::UI_TYPE type = IDToType(id);

	for (auto ui : ui_list)
	{
		if (ui->is_active)continue;
		if (ui->type == type)
		{
			target = ui;
			target->SetID(id);
			break;
		}
	}

	if (target == nullptr)
	{
		target=GenerateUI(id);
	}

	target->SetActive(true);
	return target;
}

UI::UI_TYPE UIManager::IDToType(UI::UI_ID id)
{
	switch (id)
	{
	case UI::UI_ID::DMG_TEXT:
	case UI::UI_ID::CRT_DMG_TEXT:
		return UI::UI_TYPE::DMG_TEXT;
	case UI::UI_ID::HP_BAR:
	case UI::UI_ID::HP_BAR_BACK:
		return UI::UI_TYPE::HP_BAR;
	case UI::UI_ID::EXP_BAR:
		return UI::UI_TYPE::EXP_BAR;
	case UI::UI_ID::PlayerIcon:
		break;
	default:
		break;
	}
}
