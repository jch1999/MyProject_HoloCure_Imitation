#include "framework.h"

vector<shared_ptr<const Frame>>& HPBar::GetHPBarFrames()
{
	static vector<shared_ptr<const Frame>> hpBarFrames;
	return hpBarFrames;
}

int& HPBar::GetHPBarUseCnt()
{
	static int hpBarUseCnt = 0;
	return hpBarUseCnt;
}

HPBar::HPBar(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
	,isConstant(false)
{
	if (GetHPBarFrames().empty())
	{
		InitFrame();
	}

	id = UI::UI_ID::HP_BAR;
	type = UI::UI_TYPE::HP_BAR;
	state = UI::UI_STATE::IDLE;
	additionalScale = Vector2(1, 1);
	is_active = false;

	++GetHPBarUseCnt();
}

HPBar::~HPBar()
{
	if ((--GetHPBarUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void HPBar::Update()
{
	if (!is_active)return;
	
	if (!isConstant)
	{
		switch (state)
		{
		case UI::UI_STATE::IDLE:
		{
			if (hpRate <= 0.99f)
			{
				SetState(UI_STATE::ACTIVE);
			}
			else
				return;
		}
		break;
		case UI::UI_STATE::ACTIVE:
		{
			if (hpRate > 0.99f)
			{
				SetState(UI_STATE::IDLE);
			}
		}
		break;
		default:
			break;
		}
	}
	auto& currentFrame = GetHPBarFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale * additionalScale;


	pos = target->pos + offset - Vector2((1 - uiScale.x) / 2.0f, 0) * uiSize * additionalScale;
	WorldUpdate();
}

void HPBar::Render()
{
	if (!is_active)return;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
	{

	}
		break;
	case UI::UI_STATE::ACTIVE:
	{
		VS->Set();
		PS->Set();

		WB->SetVS(0);
		CB->SetPS(0);

		GetHPBarFrames()[clipIdx]->Render();
	}
		break;
	default:
		break;
	}
}

void HPBar::InitFrame()
{
	UI::InitFrame();

	auto& hpBarFrames = GetHPBarFrames();
	if (!(hpBarFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	
	// now hp clip
	hpBarFrames.emplace_back(make_shared<const Frame>(file, 4, 484, 129, 6));
	// before hp clip
	hpBarFrames.emplace_back(make_shared<const Frame>(file, 4, 492, 129, 7));
}

void HPBar::ClearFrame()
{
	GetHPBarFrames().clear();
}

void HPBar::SetID(UI::UI_ID id)
{
	this->id = id;
	clipIdx = (UINT)id - (UINT)UI_ID::HP_BAR;
}

void HPBar::SetHpRate(float rate)
{
	hpRate = rate;
	switch (id)
	{
		case UI_ID::HP_BAR:
		{
			SetScale(Vector2(hpRate, 1.0f));
		}
		break;
		case UI_ID::HP_BAR_BACK:
		{
			SetScale(Vector2(1.0f, 1.0f));
		}
		break;
	}
}
