#include "framework.h"

NurseHorn::NurseHorn()
    :Buff(SKILL_ID::NURSE_HORN,3)
{
    weight = 3;
	skillName = "NURSE'S HORN";
	levelScripts.push_back("When defeating a target, there is a 30% chance to life-steal 2 HP. If taking a hit while HP is less than 15%, there is a chance to heal 20% HP.");
	levelScripts.push_back("When defeating a target, there is a 30% chance to life-steal 4 HP. If taking a hit while HP is less than 25%, there is a chance to heal 20% HP.");
	levelScripts.push_back("When defeating a target, there is a 30% chance to life-steal 6 HP. If taking a hit while HP is less than 30%, there is a chance to heal 20% HP.");
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
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	switch (nowLevel)
	{
	case 1:
	{
		SkillManager::Get()->nowBuffList[SkillManager::Get()->buffCnt++] = this;
		SkillManager::Get()->nurseHronActive = true;
		healAmount = 2.0f;
		hpRate = 0.2f;
	}
	break;
	case 2:
	{
		healAmount = 4.0f;
		hpRate = 0.25f;
	}
		break;
	case 3:
	{
		healAmount = 6.0f;
		hpRate = 0.3f;
	}
		break;
	default:
		break;
	}
	return true;
}
