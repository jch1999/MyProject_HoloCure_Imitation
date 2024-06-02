#include "framework.h"

BlackSmithGear::BlackSmithGear()
    :Buff(SKILL_ID::BLACKSMITH_GEAR,3)
{
	weight = 1;
}

BlackSmithGear::~BlackSmithGear()
{
}

bool BlackSmithGear::LevelDown()
{
    return false;
}

void BlackSmithGear::Update()
{
}

void BlackSmithGear::Render()
{
}

void BlackSmithGear::PostRender()
{
}

bool BlackSmithGear::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	switch (now_level)
	{
	case 1:
	{
		SkillManager::Get()->nowBuff_list[SkillManager::Get()->buffCnt++] = this;
	}
	break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
	return true;
}
