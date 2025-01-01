#include "framework.h"

ExitPanel::ExitPanel(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:Panel(inSize, inScale, inOffset)
{
	popUp = new ImageArea(make_shared<const Frame>(L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png"
		, 4.0f, 2533.0f, 240.0f, 285.0f));
	popUp->SetSize(Vector2(240.0f, 285.0f));
	popUp->SetScale(Vector2(1.5f, 1.5f));
	popUp->SetTarget(this);
	popUp->SetOffset(Vector2(0.0f, -WIN_CENTER_Y * 0.1f));
	popUp->SetState(UI_STATE::ACTIVE);
	childList.push_back(popUp);

	pauseText = new TextPrinter();
	pauseText->SetTarget(popUp);
	pauseText->SetOffset(Vector2(-75.0f, -popUp->GetSize().y * 0.5f));
	pauseText->SetTextInfo(Vector2(1.0f, 1.0f), Vector2(30.0f, 50.0f));
	pauseText->SetText("PAUSED");
	childList.push_back(pauseText);

	for (int i = 0; i < 2; i++)
	{
		Button* btn = new Button();
		btn->SetTarget(popUp);
		btn->SetOffset(Vector2(0.0f, -30.0f + 100.0f * i));
		btn->SetSize(Vector2(popUp->GetSize().x * 0.5f, popUp->GetSize().y * 0.1f));
		btn->SetScale(Vector2(1.5f, 1.5f));
		btn->GetBtnText()->SetTextInfo(Vector2(0.5f, 0.5f), Vector2(15.0f, 12.0f));
		btn->SetState(UI_STATE::IDLE);

		btns.push_back(btn);
		childList.push_back(btn);
	}
	btns[0]->GetBtnText()->SetText("Resume");
	btns[0]->GetBtnText()->SetOffset(Vector2(-35.0f, 0.0f));
	btns[1]->GetBtnText()->SetText("Quit");
	btns[1]->GetBtnText()->SetOffset(Vector2(-18.0f, 0.0f));

	id = UI::UI_ID::EXIT_PANEL;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	SetActive(false);
}

ExitPanel::~ExitPanel()
{
}

void ExitPanel::Update()
{
	if (!is_active)return;

	if (KEY_CON->Down(VK_DOWN))
	{
		selectIdx++;
		selectIdx %= 2;
	}
	else if (KEY_CON->Down(VK_UP))
	{
		selectIdx--;
		if (selectIdx < 0)
		{
			selectIdx = (int)(btns.size() - 1);
		}
	}
	else if (KEY_CON->Down(VK_RETURN))
	{
		switch (selectIdx)
		{
		case 0:
		{
			UIManager::Get()->ResetPanel();
			isPause = false;
			SetActive(false);
		}
			break;
		case 1:
			// PostQuitMessage(0); // 메모리 해제 X
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < btns.size(); i++)
	{
		if (i == selectIdx)
		{
			btns[i]->SetState(UI_STATE::ACTIVE);
			btns[i]->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			btns[i]->SetState(UI_STATE::IDLE);
			btns[i]->SetColor(Float4(0.8f, 0.8f, 0.8f, 0.8f));
		}
	}

	Panel::Update();
}

void ExitPanel::Render()
{
	if (!is_active)return;

	Panel::Render();
}

void ExitPanel::PostRender()
{
	if (!is_active)return;
	Panel::PostRender();
}

void ExitPanel::SetActive(bool active)
{
	this->is_active = active;
	for (auto c : childList)
		c->SetActive(active);
	selectIdx = 0;
	
}

