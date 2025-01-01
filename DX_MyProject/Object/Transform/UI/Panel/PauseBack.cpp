#include "framework.h"

shared_ptr<const Frame>& PauseBack::GetPauseBackFrame()
{
	static shared_ptr<const Frame> pausBackFrame;
	return pausBackFrame;
}

int& PauseBack::GetPauseBackUseCnt()
{
	static int pauseBackUseCnt = 0;
	return pauseBackUseCnt;
}

PauseBack::PauseBack(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
{
	if (GetPauseBackFrame() == nullptr)
	{
		InitFrame();
	}
	

	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.5f);
	id = UI::UI_ID::PLAYER_ICON;
	type = UI::UI_TYPE::PANEL;
	state = UI::UI_STATE::IDLE;
	additionalScale = Vector2(1, 1);
	offset = Vector2(0,0);
	is_active = true;

	++GetPauseBackUseCnt();
}

PauseBack::~PauseBack()
{
	if ((--GetPauseBackUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void PauseBack::Update()
{
	if (!is_active)return;
	switch (state)
	{
	case UI::UI_STATE::IDLE:
	{
		if (isPause)
			SetState(UI_STATE::ACTIVE);
	}
		break;
	case UI::UI_STATE::ACTIVE:
	{
		if (!isPause)
			SetState(UI_STATE::IDLE);
	}
		break;
	default:
		break;
	}

	auto& pauseBackFrame = GetPauseBackFrame();
	scale = pauseBackFrame->GetFrameSize() * uiSize / pauseBackFrame->GetFrameOriginSize() * uiScale;

	pos = target->pos + offset;
	WorldUpdate();
}

void PauseBack::Render()
{
	if (!is_active)return;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
	{
		VS->Set();
		PS->Set();

		WB->SetVS(0);
		CB->SetPS(0);

		GetPauseBackFrame()->Render();
	}
		break;
	default:
		break;
	}
}

void PauseBack::InitFrame()
{
	auto& pauseBackFrame = GetPauseBackFrame();
	if (pauseBackFrame) return;
	
	wstring file = L"Textures/UI/Black.png";
	
	pauseBackFrame= make_shared<const Frame>(file, 0, 0, 64, 64);
}

void PauseBack::ClearFrame()
{
	GetPauseBackFrame().reset();
}

void PauseBack::SetID(UI::UI_ID id)
{
	this->id = id;
}
