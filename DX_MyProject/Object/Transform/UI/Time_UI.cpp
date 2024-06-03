#include "framework.h"

Time_UI::Time_UI()
{
	Vector2 nowOffset(-37.5f,0.0f);
	Vector2 interval(15, 0);

	for (int i = 0; i < 5; i++)
	{
		LevelText* t = new LevelText();
		t->SetTarget(this);
		if (i == 2)
			nowOffset = nowOffset + interval / 2.0f;
		t->SetOffset(nowOffset);
		if (i == 2)
			nowOffset = nowOffset + interval / 2.0f;
		nowOffset = nowOffset + interval;
		t->SetActive(true);
		child_list.push_back(t);
	}

	id = UI::UI_ID::TIMER;
	type = UI::UI_TYPE::TIMER;
	state = UI::UI_STATE::IDLE;
	target = CAM;
	offset = Vector2(WIN_CENTER_X, 50.0f);
	is_active = true;
}

Time_UI::~Time_UI()
{
}

void Time_UI::Update()
{
	if (!is_active)return;

	pos = target->pos + offset;
	WorldUpdate();
	
	int nowTime = (int)EnemySpawner::Get()->nowTime;
	child_list[0]->SetClipIdx(1 + (nowTime / 600));
	child_list[1]->SetClipIdx(1 + (nowTime / 60));
	
	child_list[2]->SetClipIdx(2);

	child_list[3]->SetClipIdx(1 + ((nowTime % 60) / 10));
	child_list[4]->SetClipIdx(1 + ((nowTime % 60) % 10));

	
	for (auto child : child_list)
		child->Update();
}

void Time_UI::Render()
{
	if (!is_active)return;

	for (auto child : child_list)
		child->Render();
}

void Time_UI::PostRender()
{
}

void Time_UI::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void Time_UI::SetID(UI::UI_ID id)
{
	this->id = id;
}
