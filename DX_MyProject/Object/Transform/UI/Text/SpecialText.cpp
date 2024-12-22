#include "framework.h"

shared_ptr<Frame>& SpecialText::GetLevelUpFrame()
{
	static shared_ptr<Frame> levelUpFrame;
	return;
}

vector<vector<shared_ptr<const Frame>>>& SpecialText::GetNumberFrames()
{
	static vector<vector<shared_ptr<const Frame>>> numberFrames;
	return numberFrames;
}

int& SpecialText::GetTextUseCnt()
{
	static int textUseCnt = 0;
	return textUseCnt;
}

SpecialText::SpecialText(Vector2 inSize,Vector2 inScale,Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{
	if (GetNumberFrames().empty())
	{
		InitFrame();
	}
	
	++GetTextUseCnt();

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
	if ((--GetTextUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void SpecialText::InitFrame()
{
	auto& numberFrames = GetNumberFrames();
	if (!(numberFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	
	// level up clip
	GetLevelUpFrame()=make_shared<const Frame>(file, 4, 534, 94, 20);

	// white number clip
	{
		vector<shared_ptr<const Frame>> whiteNumberFrames;
		for (int i = 0; i <= 9; i++)
		{
			whiteNumberFrames.emplace_back(make_shared<const Frame>(file, 139 + i * 7, 484, 5, 7));
			clips.emplace_back(make_shared<Clip>(whiteNumberFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		}
		numberFrames.push_back(whiteNumberFrames);
	}
	// Yellow number clip
	{
		vector<shared_ptr<const Frame>> yellowNumberFrames;
		for (int i = 0; i <= 9; i++)
		{
			yellowNumberFrames.emplace_back(make_shared<const Frame>(file, 139 + i * 7, 493, 5, 7));
			clips.emplace_back(make_shared<Clip>(yellowNumberFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		}
		numberFrames.push_back(yellowNumberFrames);
	}
	// Red number clip
	{
		vector<shared_ptr<const Frame>> redNumberFrames;
		for (int i = 0; i <= 9; i++)
		{
			redNumberFrames.emplace_back(make_shared<const Frame>(file, 139 + i * 7, 502, 5, 7));
			clips.emplace_back(make_shared<Clip>(redNumberFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		}
		numberFrames.push_back(redNumberFrames);
	}
}

void SpecialText::ClearFrame()
{
	GetLevelUpFrame().reset();
	GetNumberFrames().clear();
}

void SpecialText::SetState(UI::UI_STATE inState)
{
	this->state = inState;
}