#include "framework.h"

vector<shared_ptr<const Frame>>& Arrow::GetArrowFrames()
{
	static vector<shared_ptr<const Frame>> arrowFrames;
	return arrowFrames;
}

int& Arrow::GetArrowUseCnt()
{
	static int arrowUseCnt = 0;
	return arrowUseCnt;
}

Arrow::Arrow(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{
	if (GetArrowFrames().empty())
	{
		InitFrame();
	}

	id = UI::UI_ID::ATK_ARROW;
	type = UI::UI_TYPE::ARROW;
	state = UI::UI_STATE::IDLE;
	is_active = false;

	++GetArrowUseCnt();
}

Arrow::~Arrow()
{
	if ((--GetArrowUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Arrow::Update()
{
	if (!is_active)return;

	const auto& currentFrame = GetArrowFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale;

	pos = target->pos;
	WorldUpdate();
}

void Arrow::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetArrowFrames()[clipIdx]->Render();
}

void Arrow::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void Arrow::SetID(UI::UI_ID id)
{
	if (this->id == id)return;

	this->id = id;;
	switch (id)
	{
	case UI::UI_ID::ATK_ARROW:
	{
		clipIdx = 0;
	}
		break;
	case UI::UI_ID::ATK_ARROW_FIXED:
	{
		clipIdx = 1;
	}
	break;
	default:
		break;
	}
}

void Arrow::InitFrame()
{
	UI::InitFrame();

	auto& arrowFrames = GetArrowFrames();
	if (!(arrowFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	// atk dir arrow 
	// normal clip
	arrowFrames.emplace_back(make_shared<const Frame>(file, 236, 494, 64, 64));
	// fixed clip
	arrowFrames.emplace_back(make_shared<const Frame>(file, 302, 494, 64, 64));
	// ? clip
	arrowFrames.emplace_back(make_shared<const Frame>(file, 368, 494, 64, 64));
}

void Arrow::ClearFrame()
{
	UI::ClearFrame();

	GetArrowFrames().clear();
}
