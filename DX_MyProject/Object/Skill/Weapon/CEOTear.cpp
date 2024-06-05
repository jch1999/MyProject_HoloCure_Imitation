#include "framework.h"

CEOTear::CEOTear()
	:Weapon(SKILL_ID::CEO_TEAR)
{
	weight = 2;
	skill_name = "CEO'S TEAR";
	level_scripts.push_back("Fires rapid tears at random targets.");
	level_scripts.push_back("Increases damage by 20%.");
	level_scripts.push_back("Shoot 2 tears.");
	level_scripts.push_back("Reduce the time between attacks by 33%.");
	level_scripts.push_back("Tears are 25% faster and increase damage by 20%.");
	level_scripts.push_back("Reduce the time between attacks by 50%.");
	level_scripts.push_back("Shoot 4 tears.");
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
