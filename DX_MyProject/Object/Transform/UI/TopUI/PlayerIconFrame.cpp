#include "framework.h"

PlayerIconFrame::PlayerIconFrame(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	
	frame=make_shared<const Frame>(file, 4, 213, 199, 87);

	// 자식 UI 생성 - playerIcon 1개, HP Bar, HP Bar Back, Hp Text
	playerIcon = new PlayerIcon();
	playerIcon->SetID(UI::UI_ID::PLAYER_ICON);
	playerIcon->SetTarget(this);
	playerIcon->SetOffset(Vector2(-140.0f, -31.0f));
	playerIcon->SetScale(Vector2(2, 1.5f));
	playerIcon->SetActive(true);

	hpBar_back = new HPBar();
	hpBar_back->SetID(UI::UI_ID::HP_BAR_BACK);
	hpBar_back->SetTarget(this);
	hpBar_back->SetOffset(Vector2(0.0f,-50.0f));
	hpBar_back->SetAddtionalScale(Vector2(3.0f, 3.3f));
	hpBar_back->SetActive(true);

	hpBar = new HPBar();
	hpBar->SetID(UI::UI_ID::HP_BAR);
	hpBar->SetTarget(this);
	hpBar->SetOffset(Vector2(0.0f, -52.0f));
	hpBar->SetAddtionalScale(Vector2(3.0f, 3.0f));
	hpBar->SetConstant(true);
	hpBar->SetState(UI::UI_STATE::ACTIVE);
	hpBar->SetActive(true);

	text_startOffset = Vector2(75.0f, -50.0f);
	for (int i = 0; i < 7; i++)
	{
		Text* t = new Text();
		t->SetID(UI_ID::TEXT);
		t->SetTarget(this);
		t->SetOffset(text_startOffset);
		t->SetScale(Vector2(0.3f, 0.3f));
		hpText.push_back(t);
		t->SetActive(false);
	}

	childList.push_back(playerIcon);
	childList.push_back(hpBar_back);
	childList.push_back(hpBar);
	for (int i = 0; i < 7; i++)
	{
		childList.push_back(hpText[i]);
	}
	
	id = UI::UI_ID::PLAYER_ICON_FRAME;
	type = UI::UI_TYPE::FRAME;
	state = UI::UI_STATE::IDLE;
	is_active = true;
}

PlayerIconFrame::~PlayerIconFrame()
{
	
}

void PlayerIconFrame::Update()
{
	scale = frame->GetFrameSize() * uiSize / frame->GetFrameOriginSize() * uiScale;

	// 자식에 추가 작업
	float hpRate = UIManager::Get()->GetPlayer()->GetHP() / UIManager::Get()->GetPlayer()->GetMaxHP();
	hpBar->SetHpRate(hpRate);
	
	// HP에 따라 text 배치
	SetHpText();

	pos = target->pos + offset;
	WorldUpdate();
	for (auto ui : childList)
	{
		ui->Update();
	}
}

void PlayerIconFrame::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	frame->Render();

	for (auto ui : childList)
		ui->Render();
}

void PlayerIconFrame::PostRender()
{
}

void PlayerIconFrame::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void PlayerIconFrame::SetID(UI::UI_ID id)
{
	this->id = id;
}

void PlayerIconFrame::SetHpText()
{
	int nowHp = round(UIManager::Get()->GetPlayer()->GetHP());
	int maxHp = round(UIManager::Get()->GetPlayer()->GetMaxHP());
	int textIdx = 0;
	Vector2 nowOffset = text_startOffset;
	Vector2 interval(10.0f, 0.0f);

	switch (nowHp / 100)
	{
	case 0:
	{
		if (nowHp >= 0)
		{
			hpText[textIdx]->SetOffset(nowOffset);
			nowOffset = nowOffset + interval;
			hpText[textIdx++]->SetText('0'+(nowHp / 10));

			hpText[textIdx]->SetOffset(nowOffset);
			nowOffset = nowOffset + interval;
			hpText[textIdx++]->SetText('0' + nowHp % 10);
		}
		else
		{
			hpText[textIdx++]->SetText('0');
			hpText[textIdx++]->SetText('0');
		}
	}
	break;
	default:
	{
		hpText[textIdx]->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		if (nowHp >= 0)
		{
			hpText[textIdx++]->SetText('0' + nowHp / 100);

			hpText[textIdx]->SetOffset(nowOffset);
			nowOffset = nowOffset + interval;
			hpText[textIdx++]->SetText('0' + (nowHp / 10) % 10);

			hpText[textIdx]->SetOffset(nowOffset);
			nowOffset = nowOffset + interval;
			hpText[textIdx++]->SetText('0' + nowHp % 10);
		}
		else
		{
			hpText[textIdx++]->SetText('0');
			hpText[textIdx++]->SetText('0');
		}
	}
	break;
	}

	// 가운데의 slash 배치.. 이지만 임시로 1로 대체
	nowOffset = nowOffset + interval/2.0f;
	hpText[textIdx]->SetText('/');
	hpText[textIdx++]->SetOffset(nowOffset);
	nowOffset = nowOffset + interval * 1.5f;
	
	switch (maxHp / 100)
	{
	case 0:
	{
		hpText[textIdx]->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		hpText[textIdx++]->SetText('0' + maxHp / 10);

		hpText[textIdx]->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		hpText[textIdx++]->SetText('0' + maxHp % 10);
	}
	break;
	default:
	{
		hpText[textIdx]->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		hpText[textIdx++]->SetText('0' + maxHp / 100);

		hpText[textIdx]->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		hpText[textIdx++]->SetText('0' + (maxHp / 10) % 10);

		hpText[textIdx]->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		hpText[textIdx++]->SetText('0' + maxHp % 10);
	}
	break;
	}

	for (int i = 0; i < 7; i++)
	{
		if (i < textIdx)
			hpText[i]->SetActive(true);
		else
			hpText[i]->SetActive(false);
	}
}
