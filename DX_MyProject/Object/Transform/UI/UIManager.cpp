#include "framework.h"

UIManager::UIManager()
{
	ui_list.resize(4);

	// DmgText
	for (int i = 0; i < 100; i++)
	{
		ui_list[0].push_back(new DmgText());
	}

	// HP Bar
	for(int i=0;i<2;i++)
		ui_list[1].push_back(new HPBar());

	// Exp Bar
	ExpBar* back = new ExpBar();
	back->SetID(UI::UI_ID::EXP_BAR_BACK);
	back->SetTarget(CAM);
	back->SetActive(true);

	ExpBar* bar = new ExpBar();
	bar->SetID(UI::UI_ID::EXP_BAR);
	bar->SetTarget(CAM);
	bar->SetActive(false);
	
	ExpBar* front = new ExpBar();
	front->SetID(UI::UI_ID::EXP_BAR_FRONT);
	front->SetTarget(CAM);
	front->SetActive(true);
	ui_list[1].push_back(back);
	ui_list[1].push_back(bar);
	ui_list[1].push_back(front);

	// ATK Arrow
	ui_list[1].push_back(new Arrow());

	// 각 Frame과 Panel에 포함되는 UI는 해당 Frame/Panel에서 child_list로 관리
	// Frame
	PlayerIconFrame* pFrame = new PlayerIconFrame();
	pFrame->SetID(UI::UI_ID::PLAYER_ICON_FRAME);
	pFrame->SetTarget(CAM);
	pFrame->SetActive(true);
	ui_list[1].push_back(pFrame);

	// Panel
	PausePanel* pause = new PausePanel();
	pause->SetTarget(CAM);
	pause->SetOffset(WIN_CENTER);
	ui_list[2].push_back(pause);
}

UIManager::~UIManager()
{
	for (auto ui : ui_list)
	{
		for (auto u : ui)
		{

			delete u;
		}
	}
}

void UIManager::Update()
{
	for (auto ui : ui_list)
	{
		for (auto u : ui)
		{
			u->Update();
		}
	}
}

void UIManager::Render()
{
	for (auto ui : ui_list)
	{
		for (auto u : ui)
		{
			u->Render();
		}
	}
}

void UIManager::PostRneder()
{
	for (auto ui : ui_list)
	{
		for (auto u : ui)
		{
			u->PostRender();
		}
	}
}

UI* UIManager::GenerateUI(UI::UI_ID id, Transform* t, Vector2 size, Vector2 offset)
{
	switch (id)
	{
	case UI::UI_ID::DMG_TEXT:
	case UI::UI_ID::CRT_DMG_TEXT:
	case UI::UI_ID::PLAYER_DMG_TEXT:
	{
		UI* dmgText = new DmgText();
		dmgText->SetID(id);
		ui_list[0].push_back(dmgText);
	}
		break;
	case UI::UI_ID::HP_BAR:
	case UI::UI_ID::HP_BAR_BACK:
	{
		UI* hp = new HPBar();
		hp->SetID(id);
		hp->SetState(UI::UI_STATE::IDLE);
		ui_list[1].push_back(hp);
		return hp;
	}
	break;
	case UI::UI_ID::SKILL_ICON:
		break;
	case UI::UI_ID::ATK_ARROW:
	case UI::UI_ID::ATK_ARROW_FIXED:
	{

	}
		break;
	default:
		break;
	}
}

UI* UIManager::GetUI(UI::UI_ID id)
{
	UI* target = nullptr;
	UI::UI_TYPE type = IDToType(id);

	switch (id)
	{
		case UI::UI_ID::DMG_TEXT:
		case UI::UI_ID::CRT_DMG_TEXT:
		case UI::UI_ID::PLAYER_DMG_TEXT:
		{
			for (auto ui : ui_list[0])
			{
				if (ui->is_active)continue;
				if (ui->type == type)
				{
					target = ui;
					target->SetID(id);
					break;
				}
			}
		}
		break;
		case UI::UI_ID::HP_BAR:
		case UI::UI_ID::HP_BAR_BACK:
		case UI::UI_ID::EXP_BAR:
		case UI::UI_ID::PLAYER_ICON:
		{
			for (auto ui : ui_list[1])
			{
				if (ui->is_active)continue;
				if (ui->type == type)
				{
					target = ui;
					target->SetID(id);
					break;
				}
			}
		}
		break;
		case UI::UI_ID::ATK_ARROW:
		case UI::UI_ID::ATK_ARROW_FIXED:
		{
			for (auto ui : ui_list[1])
			{
				if (ui->is_active)continue;
				if (ui->type == type)
				{
					target = ui;
					target->SetID(id);
					break;
				}
			}
		}
		break;
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
	case UI::UI_ID::PLAYER_DMG_TEXT:
		return UI::UI_TYPE::DMG_TEXT;
	case UI::UI_ID::HP_BAR:
	case UI::UI_ID::HP_BAR_BACK:
		return UI::UI_TYPE::HP_BAR;
	case UI::UI_ID::EXP_BAR_BACK:
	case UI::UI_ID::EXP_BAR:
	case UI::UI_ID::EXP_BAR_FRONT:
		return UI::UI_TYPE::EXP_BAR;
	case UI::UI_ID::PLAYER_ICON:
		return UI::UI_TYPE::IMAGE;
	case UI::UI_ID::ATK_ARROW:
	case UI::UI_ID::ATK_ARROW_FIXED:
		return UI::UI_TYPE::ARROW;
	default:
		break;
	}
}
