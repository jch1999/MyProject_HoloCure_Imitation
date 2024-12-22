#include "framework.h"


vector<shared_ptr<const Frame>>& Button::GetButtonFrames()
{
	static vector<shared_ptr<const Frame>> buttonFrames;
	return buttonFrames;
}

int& Button::GetButtonUseCnt()
{
	static int buttonUseCnt = 0;
	return buttonUseCnt;
}

Button::Button(Vector2 inSize,Vector2 inScale,Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{
	if (GetButtonFrames().empty())
	{
		InitFrame();
	}

	btnText = new TextPrinter();
	btnText->SetTarget(this);
	btnText->SetOffset(this->uiSize / 2.0f * this->uiScale);
	btnText->SetTextInfo(Vector2(0.3f, 0.3f), Vector2(10.0f, 20.0f));
	btnText->SetActive(true);
	childList.push_back(btnText);

	id = UI::UI_ID::BUTTON;
	type = UI::UI_TYPE::BUTTON;
	state = UI::UI_STATE::IDLE;
	is_active = false;

	++GetButtonUseCnt();
}

Button::~Button()
{
	if ((--GetButtonUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Button::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetButtonFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale;

	pos = target->pos + offset;
	WorldUpdate();

	for (auto c : childList)
		c->Update();
}

void Button::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetButtonFrames()[clipIdx]->Render();

	for (auto& c : childList)
		c->Render();
}

void Button::PostRender()
{
	if (!is_active)return;
}

void Button::InitFrame()
{
	auto& buttonFrames = GetButtonFrames();
	if (!(buttonFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	// idle clip
	buttonFrames.emplace_back(make_shared<const Frame>(file, 250.0f, 2668.0f, 180.0f, 30.0f));
	// active clip
	buttonFrames.emplace_back(make_shared<const Frame>(file, 250.0f, 2698, 180.0f, 30.0f));
}

void Button::ClearFrame()
{
	GetButtonFrames().clear();
}

void Button::SetState(UI::UI_STATE state)
{
	this->state = state;
	switch (state)
	{
	case UI::UI_STATE::IDLE:
		SetClipIdx(1);
		SetColor(Float4(0.5f, 0.5f, 0.5f, 0.5f));
		break;
	case UI::UI_STATE::ACTIVE:
		SetClipIdx(0);
		SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
}

void Button::SetID(UI::UI_ID id)
{
	this->id = id;
}
