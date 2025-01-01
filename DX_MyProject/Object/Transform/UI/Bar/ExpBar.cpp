#include "framework.h"

vector<shared_ptr<const Frame>>& ExpBar::GetExpBarFrames()
{
	static vector<shared_ptr<const Frame>> expBarFrames;
	return expBarFrames;
}

int& ExpBar::GetExpBarUseCtnt()
{
	static int expBarUseCnt = 0;
	return expBarUseCnt;
}

ExpBar::ExpBar(Vector2 inSize,Vector2 inScale,Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{
	if (GetExpBarFrames().empty())
	{
		InitFrame();
	}

	id = UI_ID::EXP_BAR;
	type = UI_TYPE::EXP_BAR; 
	additionalScale = Vector2(1, 1);
	is_active = false;

	++GetExpBarUseCtnt();
}

ExpBar::~ExpBar()
{
	if ((--GetExpBarUseCtnt()) == 0)
	{
		ClearFrame();
	}
}

void ExpBar::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetExpBarFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale;
	pos = target->pos + offset;
	WorldUpdate();
}

void ExpBar::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetExpBarFrames()[clipIdx]->Render();
}

void ExpBar::SetID(UI::UI_ID id)
{
	this->id = id;
	switch (id)
	{
	case UI_ID::EXP_BAR_BACK:
	{
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
		clipIdx = 0;
	}
		break;
	case UI_ID::EXP_BAR:
	{
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
	}
		break;
	case UI_ID::EXP_BAR_FRONT:
	{
		clipIdx = 1;
	}
		break;
	default:
		break;
	}
}

void ExpBar::SetExpRate(float rate)
{
	expRate = rate;
	clipIdx = 2 + (int)(rate * 61.0f);

	int a;
}

void ExpBar::InitFrame()
{
	auto& expBarFrames = GetExpBarFrames();
	if (!(expBarFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	// ExpBar_Back_Frame
	expBarFrames.emplace_back(new Frame(file, 4, 52, 650, 26));
	// ExpBar_Front_Frame
	expBarFrames.emplace_back(new Frame(file, 4, 80, 650, 26));
	// ExpBar
	Vector2 initPos(666, 52);
	for (int i = 0; i < 61; i++)
	{
		expBarFrames.emplace_back(new Frame(file, initPos.x, initPos.y + i * 28.0f, 650, 26));
	}
}

void ExpBar::ClearFrame()
{
	GetExpBarFrames().clear();
}
