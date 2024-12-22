#include "framework.h"

vector<shared_ptr<const Frame>>& LevelLabel::GetLevelLabelFrams()
{
	static vector<shared_ptr<const Frame>> levelLabelFrams;
	return levelLabelFrams;
}

int& LevelLabel::GetLevelLabelUseCnt()
{
	static int levelLabelUseCnt = 0;
	return levelLabelUseCnt;
}

LevelLabel::LevelLabel(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
{
	if (GetLevelLabelFrams().empty())
	{
		InitFrame();
	}

	levelText = new LevelText();
	levelText->SetID(UI_ID::TEXT);
	levelText->SetTarget(this);
	levelText->SetOffset(Vector2(10.0f, 1.0f));
	levelText->SetClipIdx(1);
	
	id = UI::UI_ID::LEVEL_LABEL;
	type = UI::UI_TYPE::LABEL;
	state = UI::UI_STATE::IDLE;
	additionalScale = Vector2(1, 1);
	is_active = false;

	++GetLevelLabelUseCnt();
}

LevelLabel::~LevelLabel()
{
	if ((--GetLevelLabelUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void LevelLabel::Update()
{
	if (!is_active)return;

	auto& curremtFrame = GetLevelLabelFrams()[clipIdx];
	scale = curremtFrame->GetFrameSize() * uiSize / curremtFrame->GetFrameOriginSize() * uiScale * additionalScale;

	pos = target->pos + offset;
	WorldUpdate();

	levelText->Update();
}

void LevelLabel::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetLevelLabelFrams()[clipIdx]->Render();
	levelText->Render();
}

void LevelLabel::InitFrame()
{
	auto& levelLabelFrams = GetLevelLabelFrams();
	if (!(levelLabelFrams.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	Vector2 initPos(139, 533);
	for (int i = 0; i < 3; i++)
	{
		levelLabelFrams.emplace_back(make_shared<const Frame>(file, 139 + i * 22, 533, 20, 9));
	}
}

void LevelLabel::ClearFrame()
{
	GetLevelLabelFrams().clear();
}

void LevelLabel::SetID(UI::UI_ID id)
{
	this->id = id;
}

void LevelLabel::SetLevel(int level)
{
	switch (clipIdx)
	{
	case 0:
	{
		levelText->SetClipIdx(1 + level);
	}
		break;
	case 1:
	{
		levelText->SetClipIdx(11 + level);
	}
		break;
	case 2:
	{
		levelText->SetClipIdx(21 + level);
	}
		break;
	}
}

void LevelLabel::SetActive(bool active)
{
	is_active = active;
	levelText->SetActive(active);
}
