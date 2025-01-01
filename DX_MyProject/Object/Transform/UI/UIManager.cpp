#include "framework.h"

UIManager::UIManager()
	:nowPanel(nullptr)
	,levelUpCnt(0)
	,isEnhance(false)
	,isReward(false)
{
	uiList.resize(4);

	// DmgText
	for (int i = 0; i < 100; i++)
	{
		uiList[0].push_back(new DmgText());
	}

	// HP Bar
	for(int i=0;i<2;i++)
		uiList[1].push_back(new HPBar());

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
	uiList[1].push_back(back);
	uiList[1].push_back(bar);
	uiList[1].push_back(front);

	// ATK Arrow
	uiList[1].push_back(new Arrow());

	// LV Text Printer
	lvText = new TextPrinter();
	lvText->SetTarget(CAM);
	lvText->SetOffset(Vector2(WIN_WIDTH-90.0f, 18.0f));
	lvText->SetTextInfo(Vector2(0.5f, 0.5f), Vector2(14.0f, 20.0f));
	lvText->SetActive(true);
	uiList[1].push_back(lvText);

	ctrText = new TextPrinter();
	ctrText->SetTarget(CAM);
	ctrText->SetOffset(Vector2(WIN_WIDTH * 0.78f, WIN_HEIGHT * 0.98f));
	ctrText->SetCharInterval(Vector2(9.5f, 15.0f));
	ctrText->SetLineLength(50);
	ctrText->SetCharScale(Vector2(0.3f, 0.3f));
	ctrText->SetText("CONFIRM: ENTER I CANCEL: ESC");
	ctrText->SetActive(true);
	uiList[1].push_back(ctrText);

	// 각 Frame과 Panel에 포함되는 UI는 해당 Frame/Panel에서 child_list로 관리
	// Frame
	PlayerIconFrame* pFrame = new PlayerIconFrame();
	pFrame->SetID(UI::UI_ID::PLAYER_ICON_FRAME);
	pFrame->SetTarget(CAM);
	pFrame->SetActive(true);
	uiList[1].push_back(pFrame);

	SkillListFrame* sFrame = new SkillListFrame();
	sFrame->SetTarget(CAM);
	sFrame->SetActive(true);
	uiList[1].push_back(sFrame);

	// Panel
	PauseBack* pause = new PauseBack();
	pause->SetTarget(CAM);
	pause->SetOffset(WIN_CENTER);
	uiList[2].push_back(pause);

	levelPanel = new LevelUpPanel();
	levelPanel->SetTarget(CAM);
	levelPanel->SetOffset(WIN_CENTER);
	uiList[2].push_back(levelPanel);

	enhancePanel = new EnhancePanel();
	enhancePanel->SetTarget(CAM);
	enhancePanel->SetOffset(WIN_CENTER);
	uiList[2].push_back(enhancePanel);
	
	rewardPanel = new RewardPanel();
	rewardPanel->SetTarget(CAM);
	rewardPanel->SetOffset(WIN_CENTER);
	uiList[2].push_back(rewardPanel);

	exitPanel = new ExitPanel();
	exitPanel->SetTarget(CAM);
	exitPanel->SetOffset(WIN_CENTER);
	uiList[2].push_back(exitPanel);

	// Timer
	uiList[2].push_back(new Time_UI());

	// Counter
	uiList[2].push_back(new Count_UI());
}

UIManager::~UIManager()
{
	for (auto ui : uiList)
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
			// EXIT_PANEL 호출
			isPause = true;
			nowPanel = exitPanel;
			nowPanel->SetActive(true);
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
		else if (isReward)
		{
			isPause = true;
			nowPanel = rewardPanel;
			nowPanel->SetActive(true);
		}
	}

	lvText->SetText("LV: " + to_string(player->GetLevel()));

	for (auto ui : uiList)
	{
		for (auto u : ui)
		{
			u->Update();
		}
	}
}

void UIManager::Render()
{
	for (auto ui : uiList)
	{
		for (auto u : ui)
		{
			u->Render();
		}
	}
}

void UIManager::PostRneder()
{
	for (auto ui : uiList)
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
		uiList[0].push_back(dmgText);
		return dmgText;
	}
		break;
	case UI::UI_ID::HP_BAR:
	case UI::UI_ID::HP_BAR_BACK:
	{
		UI* hp = new HPBar();
		hp->SetID(id);
		hp->SetState(UI::UI_STATE::IDLE);
		uiList[1].push_back(hp);
		return hp;
	}
	break;
	case UI::UI_ID::SKILL_ICON:
		break;
	case UI::UI_ID::ATK_ARROW:
	case UI::UI_ID::ATK_ARROW_FIXED:
	{
		UI* arrow = new Arrow();
		arrow->SetID(id);
		arrow->SetState(UI::UI_STATE::IDLE);
		uiList[1].push_back(arrow);
	}
		break;
	default:
		return nullptr;
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
			for (auto ui : uiList[0])
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
			for (auto ui : uiList[1])
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
			for (auto ui : uiList[1])
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

void UIManager::ResetPanel()
{
	nowPanel = nullptr;
}

void UIManager::ActivateEnhancePanel()
{
	isEnhance = true;
}

void UIManager::DeactivateEnhancePanel()
{
	isEnhance = false;
}

void UIManager::IncreaseLevelUpCnt()
{
	++levelUpCnt;
}

void UIManager::DecreaseLevelUpCnt()
{
	--levelUpCnt;
}

void UIManager::DeactivateRewardPanel()
{
	isReward = false;
}

void UIManager::ActivateRewardPanel()
{
	isReward = true;
}
