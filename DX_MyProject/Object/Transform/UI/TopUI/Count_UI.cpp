#include "framework.h"

Count_UI::Count_UI()
	:up_speed(3.0f)
	, now_coinCnt(0.0f), target_coinCnt(0.0f)
	,now_defeatCnt(0.0f),target_defeatCnt(0.0f)
{
	Vector2 nowOffset(150.0f, -10.0f);
	Vector2 interval(15, 0);
	// coin icon
	CounterIcon* coin_icon = new CounterIcon();
	coin_icon->SetClipIdx(0);
	coin_icon->SetTarget(this);
	coin_icon->SetOffset(nowOffset);
	coin_icon->SetActive(true);
	counterIcons.push_back(coin_icon);
	child_list.push_back(coin_icon);
	nowOffset = nowOffset + interval * 2.0f;
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
	
	nowOffset=Vector2(150.0f, 40.0f);
	// defeat icon
	CounterIcon* defeat_icon = new CounterIcon();
	defeat_icon->SetClipIdx(1);
	defeat_icon->SetTarget(this);
	defeat_icon->SetOffset(nowOffset);
	defeat_icon->SetActive(true);
	counterIcons.push_back(defeat_icon);
	child_list.push_back(defeat_icon);
	nowOffset = nowOffset + interval * 2.0f;
	// defeat cnt text
	for (int i = 0; i < 5; i++)
	{
		Text* t = new Text();
		t->SetTarget(this);
		t->SetOffset(nowOffset);
		nowOffset = nowOffset + interval;
		t->SetScale(Vector2(0.5f, 0.5f));
		t->SetActive(true);
		defeatCnt_text.push_back(t);
		child_list.push_back(t);
	}

	
	id = UI::UI_ID::COUNTER;
	type = UI::UI_TYPE::COUNTER;
	state = UI::UI_STATE::IDLE;
	target = CAM;
	offset = Vector2(WIN_CENTER_X + 150.0f, 50.0f);
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
	ImGui::Text("Count UI's pos : %f %f", pos.x, pos.y);
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
	if (target_coinCnt - now_coinCnt > 0.1f)
		now_coinCnt += up_speed * DELTA;
	else if (now_coinCnt > target_coinCnt)
		now_coinCnt = target_coinCnt;

	int cnt = (int)now_coinCnt;
	vector<int> cntText;
	while (cnt != 0)
	{
		cntText.push_back(cnt % 10);
		cnt /= 10;
	}
	if (cntText.size() == 0)
		cntText.push_back(0);
	else if (cntText.size() >= 2)
		reverse(cntText.begin(), cntText.end());

	for (int i = 0; i < coinCnt_text.size(); i++)
	{
		if (i < cntText.size())
		{
			coinCnt_text[i]->SetText('0' + cntText[i]);
			coinCnt_text[i]->SetActive(true);
		}
		else
		{
			coinCnt_text[i]->SetActive(false);
		}
	}
}

void Count_UI::UpdateDefeatCnt()
{
	if (target_defeatCnt - now_defeatCnt > 0.1f)
		now_defeatCnt += up_speed * DELTA;
	else if (now_defeatCnt > target_defeatCnt)
		now_defeatCnt = target_defeatCnt;

	int cnt = (int)now_defeatCnt;
	vector<int> cntText;
	while (cnt != 0)
	{
		cntText.push_back(cnt % 10);
		cnt /= 10;
	}
	if (cntText.size() == 0)
		cntText.push_back(0);
	else if(cntText.size()>=2)
		reverse(cntText.begin(), cntText.end());

	for (int i = 0; i < defeatCnt_text.size(); i++)
	{
		if (i < cntText.size())
		{
			defeatCnt_text[i]->SetText('0' + cntText[i]);
			defeatCnt_text[i]->SetActive(true);
		}
		else
		{
			defeatCnt_text[i]->SetActive(false);
		}
	}
}
