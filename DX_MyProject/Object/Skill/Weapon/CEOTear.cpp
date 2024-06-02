#include "framework.h"

CEOTear::CEOTear()
	:Weapon(SKILL_ID::CEO_TEAR)
{
	weight = 2;
}

CEOTear::~CEOTear()
{
	for (auto p : tears)
		delete p;
}

void CEOTear::UpdateTears()
{
}

bool CEOTear::LevelDown()
{
	return false;
}

void CEOTear::Update()
{
}

void CEOTear::Render()
{
}

void CEOTear::PostRender()
{
}

bool CEOTear::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}
