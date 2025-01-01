#include "framework.h"

DmgText::DmgText()
	:SpecialText()
	,speed(20.0f)
	,moveDir(Vector2(0,0))
	,lifeTime(1.5f)
{
	id = UI_ID::DMG_TEXT;
	type = UI_TYPE::DMG_TEXT; 
	uiSize = Vector2(10.0f, 14.0f);
	uiScale = Vector2(1, 1);
	additionalScale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

DmgText::~DmgText()
{
}

void DmgText::Update()
{
	if (!is_active)return;

	nowTime += DELTA;
	if (nowTime >= lifeTime)
	{
		is_active = false;
	}

	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, nowTime / 1.5f);
	
	auto& currentFrame = GetNumberFrames()[idx][clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale;
	
	pos = pos + moveDir * speed * DELTA;
	WorldUpdate();
}

void DmgText::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetNumberFrames()[idx][clipIdx]->Render();
}

void DmgText::PostRender()
{
}


void DmgText::SetID(UI::UI_ID id)
{
	this->id = id;
	switch (id)
	{
	case UI::UI_ID::DMG_TEXT:
	{
		idx = 0;
	}
	break;
	case UI::UI_ID::CRT_DMG_TEXT:
	{
		idx = 1;
	}
	break;
	case UI::UI_ID::PLAYER_DMG_TEXT:
	{
		idx = 2;
	}
	break;
	}
}

void DmgText::SetClipIdx(int idx)
{
	
	clipIdx = idx;
}

void DmgText::SetActive(bool active)
{
	UI::SetActive(active);
	nowTime = 0.0f;
}

