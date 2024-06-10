#include "framework.h"

UIManager::UIManager()
	:nowPanel(nullptr)
	,levelUpCnt(0)
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

	// Timer
	ui_list[1].push_back(new Time_UI());

	// Counter
	ui_list[1].push_back(new Count_UI());

	// LV Text Printer
	lv_text = new TextPrinter();
	lv_text->SetTarget(CAM);
	lv_text->SetOffset(Vector2(WIN_WIDTH-90.0f, 18.0f));
	lv_text->SetCharInterval(Vector2(10.0f, 20.0f));
	lv_text->SetCharScale(Vector2(0.5f, 0.5f));
	lv_text->SetActive(true);
	ui_list[1].push_back(lv_text);

	ctr_text = new TextPrinter();
	ctr_text->SetTarget(CAM);
	ctr_text->SetOffset(Vector2(WIN_WIDTH * 0.78f, WIN_HEIGHT * 0.98f));
	ctr_text->SetCharInterval(Vector2(9.5f, 15.0f));
	ctr_text->SetLineLength(50);
	ctr_text->SetCharScale(Vector2(0.3f, 0.3f));
	ctr_text->SetText("CONFIRM: ENTER I CANCEL: ESC");
	ctr_text->SetActive(true);
	ui_list[1].push_back(ctr_text);

	// 각 Frame과 Panel에 포함되는 UI는 해당 Frame/Panel에서 child_list로 관리
	// Frame
	PlayerIconFrame* pFrame = new PlayerIconFrame();
	pFrame->SetID(UI::UI_ID::PLAYER_ICON_FRAME);
	pFrame->SetTarget(CAM);
	pFrame->SetActive(true);
	ui_list[1].push_back(pFrame);

	SkillListFrame* sFrame = new SkillListFrame();
	sFrame->SetTarget(CAM);
	sFrame->SetActive(true);
	ui_list[1].push_back(sFrame);

	// Panel
	PauseBack* pause = new PauseBack();
	pause->SetTarget(CAM);
	pause->SetOffset(WIN_CENTER);
	ui_list[2].push_back(pause);

	levelPanel = new LevelUpPanel();
	levelPanel->SetTarget(CAM);
	levelPanel->SetOffset(WIN_CENTER);
	ui_list[2].push_back(levelPanel);

	enhancePanel = new EnhancePanel();
	enhancePanel->SetTarget(CAM);
	enhancePanel->SetOffset(WIN_CENTER);
	ui_list[2].push_back(enhancePanel);
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
	if (nowPanel==nullptr)
	{
		if (KEY_CON->Down(VK_ESCAPE))
		{
			// PAUSE_PANEL 호출
		}
		else if (levelUpCnt>0)
		{
			// LEVEL_UP_PANEL 호출
			isPause = true;
			nowPanel = levelPanel;
			levelPanel->SetSkillSelector();
			nowPanel->SetActive(true);
		}
		else if (isEnhance)
		{
			isPause = true;
			nowPanel = enhancePanel;
			nowPanel->SetActive(true);
		}
	}

	lv_text->SetText("LV: " + to_string(player->GetLevel()));

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
