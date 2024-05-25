#include "framework.h"

UIManager::UIManager()
{
	
}

UIManager::~UIManager()
{
	for (auto ui : ui_list)
		delete ui;
}

void UIManager::Update()
{
	for (auto ui : ui_list)
		ui->Update();
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
	case UI::UI_ID::DAMAGE_TEXT:
		break;
	case UI::UI_ID::HP_BAR:
	{
		UI* hp = new HPBar();
		hp->SetTarget(player);
		hp->SetSize(size);
		hp->SetOffset(offset);
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

	for (auto ui : ui_list)
	{
		if (ui->is_active)continue;
		if (ui->id == id)
		{
			return ui;
		}
	}

	if (target == nullptr)
	{
		GenerateUI(id);
	}
	return nullptr;
}
