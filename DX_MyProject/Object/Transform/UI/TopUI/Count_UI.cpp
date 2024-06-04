#include "framework.h"

Count_UI::Count_UI()
{
	Vector2 nowOffset(WIN_CENTER_X + 150.0f, -10.0f);
	Vector2 interval(15, 0);
	// coin cnt text
	for (int i = 0; i < 5; i++)
	{
		Text* t = new Text();
		t->SetTarget(this);
		t->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		t->SetScale(Vector2(0.5f, 0.5f));
		t->SetActive(true);
		coinCnt_text.push_back(t);
		child_list.push_back(t);
	}
	
	nowOffset=Vector2(WIN_CENTER_X + 150.0f, 40.0f);
	// defeat cnt text
	for (int i = 0; i < 5; i++)
	{
		Text* t = new Text();
		t->SetTarget(this);
		t->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		t->SetScale(Vector2(0.5f, 0.5f));
		t->SetActive(true);
		coinCnt_text.push_back(t);
		child_list.push_back(t);
	}

	
	id = UI::UI_ID::COUNTER;
	type = UI::UI_TYPE::COUNTER;
	state = UI::UI_STATE::IDLE;
	target = CAM;
	offset = Vector2(WIN_CENTER_X, 50.0f);
	is_active = true;
}

Count_UI::~Count_UI()
{
}

void Count_UI::Update()
{
	if (!is_active)return;

	pos = target->pos + offset;
	WorldUpdate();

	target_coinCnt = (float)ItemSpawner::Get()->nowCoinValue;
	target_defeatCnt = (float)EnemySpawner::Get()->defeatCnt;

	UpdateCoinCnt();
	UpdateDefeatCnt();

	for (auto child : child_list)
		child->Update();
}

void Count_UI::Render()
{
	if (!is_active)return;

	for (auto child : child_list)
		child->Render();
}

void Count_UI::PostRender()
{
}

void Count_UI::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void Count_UI::SetID(UI::UI_ID id)
{
	this->id = id;
}

void Count_UI::UpdateCoinCnt()
{
}

void Count_UI::UpdateDefeatCnt()
{
}
