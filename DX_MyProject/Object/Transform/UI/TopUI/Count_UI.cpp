#include "framework.h"

Count_UI::Count_UI(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
	, upSpeed(100.0f)
	, nowCoinCnt(0.0f), targetCoinCnt(0.0f)
	,nowDefeatCnt(0.0f),targetDefeatCnt(0.0f)
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
	childList.push_back(coin_icon);
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
		coinCntText.push_back(t);
		childList.push_back(t);
	}

	nowOffset = Vector2(150.0f, 40.0f);
	// defeat icon
	CounterIcon* defeat_icon = new CounterIcon();
	defeat_icon->SetClipIdx(1);
	defeat_icon->SetTarget(this);
	defeat_icon->SetOffset(nowOffset);
	defeat_icon->SetActive(true);
	counterIcons.push_back(defeat_icon);
	childList.push_back(defeat_icon);
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
		defeatCntText.push_back(t);
		childList.push_back(t);
	}
	
	id = UI::UI_ID::COUNTER;
	type = UI::UI_TYPE::COUNTER;
	state = UI::UI_STATE::IDLE;
	target = CAM;
	is_active = true;
}

Count_UI::~Count_UI()
{
	counterIcons.clear(); 
	coinCntText.clear();
	defeatCntText.clear();
}

void Count_UI::Update()
{
	if (!is_active)return;

	pos = target->pos + offset;
	WorldUpdate();

	targetCoinCnt = (float)ItemSpawner::Get()->nowCoinValue;
	targetDefeatCnt = (float)EnemySpawner::Get()->defeatCnt;

	UpdateCoinCnt();
	UpdateDefeatCnt();

	for (auto child : childList)
		child->Update();
}

void Count_UI::Render()
{
	if (!is_active)return;

	for (auto child : childList)
		child->Render();
}

void Count_UI::PostRender()
{
	//ImGui::Text("Count UI's pos : %f %f", pos.x, pos.y);
}

void Count_UI::InitFrame()
{
}

void Count_UI::ClearFrame()
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

void Count_UI::SetClipIdx(int idx)
{
	this->clipIdx = idx;
}

void Count_UI::UpdateCoinCnt()
{
	if (targetCoinCnt - nowCoinCnt > 0.1f)
		nowCoinCnt += upSpeed * DELTA;
	else if (nowCoinCnt > targetCoinCnt)
		nowCoinCnt = targetCoinCnt;

	int cnt = round(nowCoinCnt);
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

	for (int i = 0; i < coinCntText.size(); i++)
	{
		if (i < cntText.size())
		{
			coinCntText[i]->SetText('0' + cntText[i]);
			coinCntText[i]->SetActive(true);
		}
		else
		{
			coinCntText[i]->SetActive(false);
		}
	}
}

void Count_UI::UpdateDefeatCnt()
{
	if (targetDefeatCnt - nowDefeatCnt > 0.1f)
		nowDefeatCnt += upSpeed * DELTA;
	else if (nowDefeatCnt > targetDefeatCnt)
		nowDefeatCnt = targetDefeatCnt;

	int cnt = round(nowDefeatCnt);
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

	for (int i = 0; i < defeatCntText.size(); i++)
	{
		if (i < cntText.size())
		{
			defeatCntText[i]->SetText('0' + cntText[i]);
			defeatCntText[i]->SetActive(true);
		}
		else
		{
			defeatCntText[i]->SetActive(false);
		}
	}
}
