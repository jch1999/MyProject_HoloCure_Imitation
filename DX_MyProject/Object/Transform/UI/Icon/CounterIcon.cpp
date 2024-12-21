#include "framework.h"

vector<shared_ptr<Frame>> CounterIcon::counterIconFrmaes;
bool CounterIcon::bInited=false;
int CounterIcon::CounterIconCnt=0;

CounterIcon::CounterIcon()
{
	if (!bInited)
	{
		Init();
	}

	id = UI::UI_ID::COUNTER_ICON;
	type = UI::UI_TYPE::ICON;
	state = UI::UI_STATE::IDLE;
	uiSize = Vector2(15.0f, 15.0f);
	uiScale = Vector2(1.5f, 1.5f);
	additionalScale = Vector2(1.0f, 1.0f);
	offset = Vector2(0, 0);
	is_active = true;

	++CounterIconCnt;
}

CounterIcon::~CounterIcon()
{
	if ((--CounterIconCnt) == 0)
	{
		counterIconFrmaes.clear();
		bInited = false;
	}
}

void CounterIcon::Init()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	for (int i = 0; i < 2; i++)
	{
		counterIconFrmaes.push_back(make_shared<Frame>(file, 167.0f + 17.0f * i, 567.0f, 15.0f, 16.0f));
		clips.push_back(make_shared<Clip>(counterIconFrmaes, Clip::CLIP_TYPE::END, 1));
	}

	bInited = true;
}

void CounterIcon::Update()
{
	if (!is_active)return;

	scale = clips[clipIdx]->GetFrameSize() * uiSize / clips[clipIdx]->GetFrameOriginSize() * uiScale * additionalScale;
	clips[clipIdx]->Update();

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

	clips[clipIdx]->Render();
}

void CounterIcon::PostRender()
{
}

void CounterIcon::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void CounterIcon::SetID(UI::UI_ID id)
{
	this->id = id;
}
