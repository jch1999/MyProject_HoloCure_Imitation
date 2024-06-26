#include "framework.h"

LightEffect::LightEffect()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	for (int i = 0; i < 5; i++)
	{
		ImageArea* light = new ImageArea(new Frame(file, 218.0f, 953.0f, 24.0f, 43.0f));
		light->SetSize(Vector2(24.0f, 43.0f));
		lightEffect.push_back(light);
		light->SetAngle(72.0f * M_PI / 180.0f * i);
		light->SetTarget(this);
		child_list.push_back(light);
	}
}

LightEffect::~LightEffect()
{
}

void LightEffect::Update()
{
	if (!is_active)return;

	if (target != nullptr)
		pos = target->pos + offset;
	for (auto c : child_list)
	{
		c->SetOffset(Vector2(round(cosf(90.0f * M_PI / 180.0f + c->GetAngle())), round(sinf(90.0f * M_PI / 180.0f + c->GetAngle()))) * dist * -1.0f
			+ Vector2(0.0f, -10.0f));
	}
	lightEffect[1]->SetOffset(lightEffect[1]->GetOffset() + Vector2(10.0f, -15.0f));
	lightEffect[4]->SetOffset(lightEffect[4]->GetOffset() + Vector2(-10.0f, -15.0f));
	lightEffect[2]->SetOffset(lightEffect[2]->GetOffset() + Vector2(-15.0f, 10.0f));
	lightEffect[3]->SetOffset(lightEffect[3]->GetOffset() + Vector2(15.0f, 10.0f));
	WorldUpdate();
	for (auto c : child_list)
		c->Update();
}

void LightEffect::Render()
{
	if (!is_active)return;

	for (auto c : child_list)
		c->Render();
}

void LightEffect::PostRender()
{
	ImGui::SliderFloat("Dist", &dist, 0.0f, 150.0f);
}

void LightEffect::SetState(UI::UI_STATE state)
{
	this->state = state;
	for (auto c : child_list)
		c->SetState(state);
}

void LightEffect::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LightEffect::SetScale(Vector2 _scale)
{
	this->ui_scale = _scale;
	for (auto i : lightEffect)
		i->SetScale(_scale);
}
