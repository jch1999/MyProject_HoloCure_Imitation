#include "framework.h"

shared_ptr<Frame> SpecialText::LevelUpFrame;
vector< shared_ptr<const Frame>> SpecialText::WhiteNumberFrames;
vector< shared_ptr<const Frame>> SpecialText::YellowNumberFrames;
vector< shared_ptr<const Frame>> SpecialText::RedNumberFrames;
bool SpecialText:: bInited=false;
int SpecialText::TextUseCnt=0;

SpecialText::SpecialText()
{
	if (!bInited)
	{
		Init();
	}
	
	++TextUseCnt;

	id = UI_ID::LEVEL_TEXT;
	type = UI_TYPE::TEXT;
	uiSize = Vector2(10.0f, 14.0f);
	uiScale = Vector2(1, 1);
	additionalScale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

SpecialText::~SpecialText()
{
	if ((--TextUseCnt) == 0)
	{
		bInited = false;
	}
}

void SpecialText::Init()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	
	// level up clip
	LevelUpFrame=make_shared<const Frame>(file, 4, 534, 94, 20);

	// white number clip
	for (int i = 0; i <= 9; i++)
	{
		WhiteNumberFrames.push_back(make_shared<const Frame>(file, 139 + i * 7, 484, 5, 7));
		clips.push_back(make_shared<Clip>(WhiteNumberFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	}
	// Yellow number clip
	for (int i = 0; i <= 9; i++)
	{
		YellowNumberFrames.push_back(make_shared<const Frame>(file, 139 + i * 7, 493, 5, 7));
		clips.push_back(make_shared<Clip>(YellowNumberFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	}
	// Red number clip
	for (int i = 0; i <= 9; i++)
	{
		RedNumberFrames.push_back(make_shared<const Frame>(file, 139 + i * 7, 502, 5, 7));
		clips.push_back(make_shared<Clip>(RedNumberFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	}

	bInited = true;
}

void SpecialText::SetState(UI::UI_STATE inState)
{
	this->state = inState;
}