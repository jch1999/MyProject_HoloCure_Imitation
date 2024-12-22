#include "framework.h"

vector<shared_ptr<const Frame>>& IconFrame::GetIconFrameFrames()
{
	static vector<shared_ptr<const Frame>> iconFrameFrames;
	return iconFrameFrames;
}

int& IconFrame::GetIconFrameUseCnt()
{
	static int iconFrameUseCnt = 0;
	return iconFrameUseCnt;
}

IconFrame::IconFrame(Vector2 inSize,Vector2 inScale, Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{
	if (GetIconFrameFrames().empty())
	{
		InitFrame();
	}

	id = UI::UI_ID::SKILL_ICON_FRAME;
	type = UI::UI_TYPE::FRAME;
	state = UI::UI_STATE::IDLE;
	is_active = false;

	++GetIconFrameUseCnt();
}

IconFrame::~IconFrame()
{
	if ((--GetIconFrameUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void IconFrame::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetIconFrameFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale;

	pos = target->pos + offset;
	WorldUpdate();
}

void IconFrame::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetIconFrameFrames()[clipIdx]->Render();
}

void IconFrame::InitFrame()
{
	auto& iconFrameFrames = GetIconFrameFrames();
	if (!(iconFrameFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	
	// weapon icon frame clip
	iconFrameFrames.emplace_back(make_shared<const Frame>(file, 189.0f, 1872.0f, 35.0f, 36.0f));
	// buff icon frame clip
	iconFrameFrames.emplace_back(make_shared<const Frame>(file, 152.0f, 1872.0f, 35.0f, 36.0f));
	// Stat iconframe clip
	iconFrameFrames.emplace_back(make_shared<const Frame>(file, 115.0f, 1872.0f, 35.0f, 36.0f));
	iconFrameFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 1872.0f, 35.0f, 36.0f));
	// Default Iconframe clip
	iconFrameFrames.emplace_back(make_shared<const Frame>(file, 138.0f, 4078.0f, 32.0f, 32.0f));
	iconFrameFrames.emplace_back(make_shared<const Frame>(file, 172.0f, 4078.0f, 33.0f, 33.0f));
}

void IconFrame::ClearFrame()
{
	GetIconFrameFrames().clear();
}
