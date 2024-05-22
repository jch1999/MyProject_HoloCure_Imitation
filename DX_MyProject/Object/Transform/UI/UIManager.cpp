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

void UIManager::GenerateUI(UI::UI_ID id, Transform* t, Vector2 offset)
{
}

UI* UIManager::GetUI(UI::UI_ID id)
{
	for (auto ui : ui_list)
		if (ui->id == id)
			return ui;
	return nullptr;
}
