#include "framework.h"

LightEffect::LightEffect()
{
	InitFrame();
	for (int i = 0; i < 5; i++)
	{
		ImageArea* light = new ImageArea(lightEffectFrame);
		light->SetSize(Vector2(24.0f, 43.0f));
		(light);
		light->SetAngle(72.0f * M_PI / 180.0f * i);
		light->SetTarget(this);
		childList.push_back(light);
	}
}

LightEffect::~LightEffect()
{
	ClearFrame();
}

void LightEffect::Update()
{
	if (!is_active)return;

	if (target != nullptr)
		pos = target->pos + offset;

	for (int i = 0; i < lightEffect.size(); i++)
	{
		lightEffect[i]->SetAngle(72.0f * M_PI / 180.0f * i + this->rot.z);
	}

	for (auto c : childList)
	{
		c->SetOffset(Vector2((cosf(90.0f * M_PI / 180.0f + c->GetAngle())), (sinf(90.0f * M_PI / 180.0f + c->GetAngle()))) * dist * -1.0f
			+ Vector2(0.0f, 15.0f));
	}
	//lightEffect[1]->SetOffset(lightEffect[1]->GetOffset() + Vector2(10.0f, -15.0f));
	//lightEffect[4]->SetOffset(lightEffect[4]->GetOffset() + Vector2(-10.0f, -15.0f));
	//lightEffect[2]->SetOffset(lightEffect[2]->GetOffset() + Vector2(-15.0f, 10.0f));
	//lightEffect[3]->SetOffset(lightEffect[3]->GetOffset() + Vector2(15.0f, 10.0f));

	WorldUpdate();
	for (auto c : childList)
		c->Update();
}

void LightEffect::Render()
{
	if (!is_active)return;

	for (auto c : childList)
		c->Render();
}

void LightEffect::SetState(UI::UI_STATE state)
{
	this->state = state;
	for (auto c : childList)
	{
		c->SetState(state);
	}
}

void LightEffect::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LightEffect::SetScale(Vector2 inScale)
{
	this->uiScale = inScale;
	for (auto i : lightEffect)
	{
		i->SetScale(inScale);
	}
}

void LightEffect::InitFrame()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	lightEffectFrame = make_shared<const Frame>(file, 218.0f, 953.0f, 24.0f, 43.0f);
}

void LightEffect::ClearFrame()
{
	lightEffectFrame.reset();
}
