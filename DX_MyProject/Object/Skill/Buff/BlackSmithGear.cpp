#include "framework.h"

BlackSmithGear::BlackSmithGear()
    :Buff(SKILL_ID::BLACKSMITH_GEAR,3)
{
	weight = 1;
	level_scripts.push_back("Normal anvils can be used twice. Only applies to anvils since taking this item.");
	level_scripts.push_back("Normal anvils can be used twice. Weapon enhancements increase damage by 2.5 instead of 2 per level.");
	level_scripts.push_back("Normal anvils can be used twice. Weapon enhancements increase damage by 3 instead of 2 per level.");
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
