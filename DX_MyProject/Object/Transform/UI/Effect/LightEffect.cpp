#include "framework.h"

shared_ptr<const Frame>& LightEffect::GetLightEffectFrame()
{
	static shared_ptr<const Frame> lightEffectFrame;
	return lightEffectFrame;
}

int& LightEffect::GetLightEffectUseCnt()
{
	static int lightEffectUseCnt = 0;
	return lightEffectUseCnt;
}

LightEffect::LightEffect()
	:UI()
{
	InitFrame();
	for (int i = 0; i < 5; i++)
	{
		ImageArea* light = new ImageArea(GetLightEffectFrame());
		light->SetSize(Vector2(24.0f, 43.0f));
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

	for (int i = 0; i < childList.size(); i++)
	{
		childList[i]->SetAngle(72.0f * M_PI / 180.0f * i + this->rot.z); 
		childList[i]->SetOffset(Vector2((cosf(90.0f * M_PI / 180.0f + childList[i]->GetAngle())), (sinf(90.0f * M_PI / 180.0f + childList[i]->GetAngle()))) * dist * -1.0f
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
	for (auto light : childList)
	{
		light->SetScale(inScale);
	}
}

void LightEffect::InitFrame()
{
	auto& lightEffectFrame = GetLightEffectFrame();
	
	if (lightEffectFrame) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	lightEffectFrame = make_shared<const Frame>(file, 218.0f, 953.0f, 24.0f, 43.0f);
}

void LightEffect::ClearFrame()
{
	GetLightEffectFrame().reset();
}
