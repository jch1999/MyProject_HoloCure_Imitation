#include "framework.h"

PlayerIconFrame::PlayerIconFrame()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4, 213, 199, 87));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 10.f));

	// 자식 UI 생성 - playerIcon 1개, HP Bar, HP Bar Back, Hp Text
	playerIcon = new Icon();
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

	child_list.push_back(playerIcon);
	child_list.push_back(hpBar_back);
	child_list.push_back(hpBar);
	
	id = UI::UI_ID::PLAYER_ICON_FRAME;
	type = UI::UI_TYPE::FRAME;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(199.0f, 86.0f);
	ui_scale = Vector2(2.0f, 2.0f);
	offset = Vector2(180, 85);
	is_active = true;
}

PlayerIconFrame::~PlayerIconFrame()
{
	
}

void PlayerIconFrame::Update()
{
	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[0]->Update();

	// 자식에 추가 작업
	float hpRate = UIManager::Get()->GetPlayer()->GetHP() / UIManager::Get()->GetPlayer()->GetMaxHP();
	hpBar->SetHpRate(hpRate);

	pos = target->pos + offset;
	WorldUpdate();
	for (auto ui : child_list)
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

	clips[clip_idx]->Render();

	for (auto ui : child_list)
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
