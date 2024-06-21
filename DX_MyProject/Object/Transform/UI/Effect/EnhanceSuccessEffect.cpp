#include "framework.h"

EnhanceSuccessEffect::EnhanceSuccessEffect()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	for (int i = 0; i < 5; i++)
	{
		ImageArea* light = new ImageArea(new Frame(file, 218.0f, 953.0f, 24.0f, 43.0f));
		lightEffect.push_back(light);
		light->rot.z = 72.0f * i;
		light->SetTarget(this);
		child_list.push_back(light);
	}
}

EnhanceSuccessEffect::~EnhanceSuccessEffect()
{
}

void EnhanceSuccessEffect::Update()
{
	if (!is_active)return;

	if (target != nullptr)
		pos = target->pos + offset;
	for (auto c : child_list)
	{
		c->SetOffset(Vector2(cosf(90.0f + c->rot.z), -sinf(90.0f + c->rot.z)) * dist);
	}
	WorldUpdate();
	for (auto c : child_list)
		c->Update();
}

void EnhanceSuccessEffect::Render()
{
	if (!is_active)return;

	for (auto c : child_list)
		c->Render();
}

void EnhanceSuccessEffect::PostRender()
{
}

void EnhanceSuccessEffect::SetState(UI::UI_STATE state)
{
	this->state = state;
	for (auto c : child_list)
		c->SetState(state);
}

void EnhanceSuccessEffect::SetID(UI::UI_ID id)
{
	this->id = id;
}
