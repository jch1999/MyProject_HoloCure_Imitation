#include "framework.h"
#include "PickRangeUp.h"

PickRangeUp::PickRangeUp()
	:Skill(SKILL_ID::PICK_UP, SKILL_TYPE::STAT, 1)
{
	weight = 4;
	skillName = "PICK UP RANGE UP";
	levelScripts.push_back("Pick Up Range +20% Up.");
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
	player->IncreasePickUpRange();
	if (player->GetPickUpRnage() == player->GetPickUpRangeColNum() - 1)
	{
		// SkillManager::Get()->totalWeightS -= this->weight;
		
	}
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

bool PickRangeUp::Enhance()
{
	return false;
}
