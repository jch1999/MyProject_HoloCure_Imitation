#include "framework.h"

PikiPikiPiman::PikiPikiPiman()
    :Buff(SKILL_ID::PIKIPIK_PIMAN,3)
{
    weight = 4;
	level_scripts.push_back("Gain 15 Max HP. For every 6 points of total Max HP, increase damage of Main Weapon by 1%.");
	level_scripts.push_back("Gain 20 Max HP. For every 5 points of total Max HP, increase damage of Main Weapon by 1%.");
	level_scripts.push_back("Gain 25 Max HP. For every 4 points of total Max HP, increase damage of Main Weapon by 1%.");
}

PikiPikiPiman::~PikiPikiPiman()
{
}

bool PikiPikiPiman::LevelDown()
{
    return false;
}

void PikiPikiPiman::Update()
{
}

void PikiPikiPiman::Render()
{
}

void PikiPikiPiman::PostRender()
{
}

bool PikiPikiPiman::LevelUp()
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
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
	return true;
}
