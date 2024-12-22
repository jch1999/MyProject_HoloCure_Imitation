#include "framework.h"

vector<shared_ptr<const Frame>>& ChargeEffect::GetChangeEffectFrames()
{
	static vector<shared_ptr<const Frame>> changeEffectFrames;
	return changeEffectFrames;
}

int& ChargeEffect::GetChangeEffectUseCnt()
{
	static int changeEffectUseCnt = 0;
	return changeEffectUseCnt;
}

ChargeEffect::ChargeEffect()
{
	if (GetChangeEffectFrames().empty())
	{
		InitFrame();
	}
	clips.emplace_back(make_shared<Clip>(GetChangeEffectFrames(), Clip::CLIP_TYPE::LOOP, 0.5f / 15.0f));

	type = UI_TYPE::EFFECT;
	id = UI_ID::CHARGE_EFFECT;
	state = UI_STATE::IDLE;
	uiSize = Vector2(128.0f, 128.0f);
	uiScale = Vector2(1, 1);
	offset = Vector2(0.0f, 0.0f);

	++GetChangeEffectUseCnt();
}

ChargeEffect::~ChargeEffect()
{
	if ((--GetChangeEffectUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void ChargeEffect::Update()
{
	if (!is_active)return;
	
	if (target != nullptr)
		pos = target->pos + offset;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
		clips[clipIdx]->Update();
		break;
	default:
		break;
	}

	scale = clips[clipIdx]->GetFrameSize() * uiSize / clips[clipIdx]->GetFrameOriginSize() * uiScale;
	
	WorldUpdate();
}

void ChargeEffect::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	
	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
	{
		clips[clipIdx]->Render();
	}
		break;
	default:
		break;
	}
}

void ChargeEffect::PostRender()
{
}

void ChargeEffect::InitFrame()
{
	auto& changeEffectFrames = GetChangeEffectFrames();
	if (!(changeEffectFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			changeEffectFrames.emplace_back(make_shared<const Frame>(file, 4.0f + 130.0f * j, 1058.0f + 130.0f * i, 128.0f, 128.0f));
		}
	}
}

void ChargeEffect::ClearFrame()
{
	GetChangeEffectFrames().clear();
}

void ChargeEffect::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void ChargeEffect::SetID(UI::UI_ID id)
{
	this->id = id;
}
