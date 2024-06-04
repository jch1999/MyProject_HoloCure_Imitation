#include "framework.h"
#include "PickRangeUp.h"

PickRangeUp::PickRangeUp()
	:Skill(SKILL_ID::PICK_UP, SKILL_TYPE::STAT, 1)
{
	weight = 4;
	level_scripts.push_back("Pick Up Range +20% Up.");
}

PickRangeUp::~PickRangeUp()
{
}

void PickRangeUp::Update()
{
	return;
}

void PickRangeUp::Render()
{
	return;
}

void PickRangeUp::PostRender()
{
}

bool PickRangeUp::LevelUp()
{
	player->SetPickUpRange(player->GetPickUpRnage() + 1);
	return true;
}

bool PickRangeUp::LevelDown()
{
	return false;
}

bool PickRangeUp::GetEnhanceAble()
{
	return false;
}

void PickRangeUp::Enhance(float enhanceAmount)
{
}
