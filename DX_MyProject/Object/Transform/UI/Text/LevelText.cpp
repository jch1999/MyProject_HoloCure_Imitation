#include "framework.h"

LevelText::LevelText()
	:SpecialText()
{
	id = UI_ID::LEVEL_TEXT;
	type = UI_TYPE::TEXT;
	uiSize = Vector2(10.0f, 14.0f);
	uiScale = Vector2(1, 1);
	additionalScale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

LevelText::~LevelText()
{
}

void LevelText::Update()
{
	if (!is_active)return;

	scale = frame->GetFrameSize() * uiSize / frame->GetFrameOriginSize() * uiScale;

	pos = target->pos + offset;
	WorldUpdate();
}

void LevelText::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	frame->Render();
}

void LevelText::PostRender()
{
}

void LevelText::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LevelText::SetClipIdx(int idx)
{
	clipIdx = idx;
	switch (clipIdx)
	{
	case 0:
	{
		frame = levelUpFrame;
	}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	{
		frame = numberFrames[0][clipIdx];
	}
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	{
		frame = numberFrames[0][clipIdx-10];
	}
		break;
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	{
		frame = numberFrames[0][clipIdx - 20];
	}
		break;
	default:
		break;
	}
}
