#include "framework.h"

vector<shared_ptr<const Frame>>& CounterIcon::GetCounterIconFrames()
{
	static vector<shared_ptr<const Frame>> counterIconFrames;
	return counterIconFrames;
}

int& CounterIcon::GetCounterIconUseCnt()
{
	static int counterIconUseCnt = 0;
	return counterIconUseCnt;
}

CounterIcon::CounterIcon(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{
	if (GetCounterIconFrames().empty())
	{
		InitFrame();
	}

	id = UI::UI_ID::COUNTER_ICON;
	type = UI::UI_TYPE::ICON;
	state = UI::UI_STATE::IDLE;
	additionalScale = Vector2(1.0f, 1.0f);
	
	is_active = true;

	++GetCounterIconUseCnt();
}

CounterIcon::~CounterIcon()
{
	if ((--GetCounterIconUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void CounterIcon::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetCounterIconFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale * additionalScale;

	pos = target->pos + offset;
	WorldUpdate();
}

void CounterIcon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetCounterIconFrames()[clipIdx]->Render();
}

void CounterIcon::InitFrame()
{
	auto& counterIconFrames = GetCounterIconFrames();
	if (!(counterIconFrames.empty())) return;

 	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	for (int i = 0; i < 2; i++)
	{
		counterIconFrames.push_back(make_shared<Frame>(file, 167.0f + 17.0f * i, 567.0f, 15.0f, 16.0f));
	}
}

void CounterIcon::ClearFrame()
{
	GetCounterIconFrames().clear();
}

void CounterIcon::SetID(UI::UI_ID id)
{
	this->id = id;
}
