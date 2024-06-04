#include "framework.h"

NurseHorn::NurseHorn()
    :Buff(SKILL_ID::NURSE_HORN,3)
{
    weight = 3;
	level_scripts.push_back("When defeating a target, there is a 30% chance to life-steal 2 HP. If taking a hit while HP is less than 15%, there is a chance to heal 20% HP.");
	level_scripts.push_back("When defeating a target, there is a 30% chance to life-steal 4 HP. If taking a hit while HP is less than 25%, there is a chance to heal 20% HP.");
	level_scripts.push_back("When defeating a target, there is a 30% chance to life-steal 6 HP. If taking a hit while HP is less than 30%, there is a chance to heal 20% HP.");
}

NurseHorn::~NurseHorn()
{
}

bool NurseHorn::LevelDown()
{
    return false;
}

void NurseHorn::Update()
{
}

void NurseHorn::Render()
{
}

void NurseHorn::PostRender()
{
}

bool NurseHorn::LevelUp()
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
