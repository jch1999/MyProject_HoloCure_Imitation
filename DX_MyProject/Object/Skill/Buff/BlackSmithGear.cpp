#include "framework.h"

BlackSmithGear::BlackSmithGear()
    :Buff(SKILL_ID::BLACKSMITH_GEAR,3)
{
	weight = 1;
	skillName = "BLACK SMITH GEAR";
	levelScripts.push_back("Normal anvils can be used twice. Only applies to anvils since taking this item.");
	levelScripts.push_back("Normal anvils can be used twice. Weapon enhancements increase damage by 2.5 instead of 2 per level.");
	levelScripts.push_back("Normal anvils can be used twice. Weapon enhancements increase damage by 3 instead of 2 per level.");
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
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	switch (nowLevel)
	{
	case 1:
	{
		SkillManager::Get()->nowBuffList[SkillManager::Get()->buffCnt++] = this;
		ItemSpawner::Get()->anvilUseCnt = 2;
	}
		break;
	case 2:
		ItemSpawner::Get()->enhanceDmg = 2.5f;
		break;
	case 3:
		ItemSpawner::Get()->enhanceDmg = 3.0f;
		break;
	default:
		break;
	}
	return true;
}
