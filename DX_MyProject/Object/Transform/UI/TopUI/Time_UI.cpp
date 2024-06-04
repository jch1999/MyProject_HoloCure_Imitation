#include "framework.h"

Time_UI::Time_UI()
{
	Vector2 nowOffset(-25.0f,-10.0f);
	Vector2 interval(15, 0);
	// Stage text
	for (int i = 0; i < 5; i++)
	{
		Text* t = new Text();
		t->SetTarget(this);
		t->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		t->SetScale(Vector2(0.5f, 0.5f));
		t->SetActive(true);
		stage_text.push_back(t);
		child_list.push_back(t);
	}
	stage_text[0]->SetText('S');
	stage_text[1]->SetText('t');
	stage_text[2]->SetText('a');
	stage_text[3]->SetText('g');
	stage_text[4]->SetText('e');

	// Time
	nowOffset = Vector2(-35.0f, 20.0f);
	for (int i = 0; i < 5; i++)
	{
		Text* t = new Text();
		t->SetTarget(this);
		if (i == 2)
			nowOffset = nowOffset + interval / 2.0f;
		t->SetOffset(nowOffset);
		if (i == 2)
			nowOffset = nowOffset + interval / 2.0f;
		nowOffset = nowOffset + interval;
		t->SetScale(Vector2(0.3f, 0.3f));
		t->SetActive(true);
		time_text.push_back(t);
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
	time_text[0]->SetText('0'+(nowTime / 600));
	time_text[1]->SetText('0' + (nowTime / 60));
	
	time_text[2]->SetText('/');

	time_text[3]->SetText('0' + ((nowTime % 60) / 10));
	time_text[4]->SetText('0' + ((nowTime % 60) % 10));

	
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
