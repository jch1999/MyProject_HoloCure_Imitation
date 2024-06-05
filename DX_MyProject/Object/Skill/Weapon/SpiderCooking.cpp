#include "framework.h"

SpiderCooking::SpiderCooking()
	:Weapon(Skill::SKILL_ID::SPIDER_COOKING)
	,poision(nullptr)
{
	weight = 4;
	skill_name = "SPIDER COOKING";
	level_scripts.push_back("Create an area of miasma around, dealing slow damage to enemies inside.");
	level_scripts.push_back("Increase area by 15%.");
	level_scripts.push_back("Increase damage by 30%.");
	level_scripts.push_back("Increase area by 25%.");
	level_scripts.push_back("Increase frequency of hits by 20%.");
	level_scripts.push_back("Increase damage by 60%.");
	level_scripts.push_back("Add small knockback on hit.");
}

SpiderCooking::~SpiderCooking()
{
	delete poision;
}

void SpiderCooking::Update()
{
	if (now_level == 0)return;

	UpdatePoision();
}

void SpiderCooking::Render()
{
	if (now_level == 0)return;
}

void SpiderCooking::PostRender()
{
}

bool SpiderCooking::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool SpiderCooking::LevelDown()
{
	return false;
}

void SpiderCooking::UpdatePoision()
{
}
