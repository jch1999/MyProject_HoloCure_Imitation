#include "framework.h"

PsychoAxe::PsychoAxe()
	:Weapon(Skill::SKILL_ID::PSYCHO_AXE)
{
	weight = 3;
	level_scripts.push_back("Throw an axe that spirals outward from the player.");
	level_scripts.push_back("Increase size of axe by 20%. Increase damage of axe by 20%.");
	level_scripts.push_back("Reduce delay between attacks by 20%.");
	level_scripts.push_back("Increase damage by 33%, and size by 20%.");
	level_scripts.push_back("Remove hit limit, and lasts 1 second longer.");
	level_scripts.push_back("Increase attack size by 50%.");
	level_scripts.push_back("Increase damage by 50%.");
}

PsychoAxe::~PsychoAxe()
{
}

void PsychoAxe::Update()
{
	if (now_level == 0)return;

	UpdateAxes();
}

void PsychoAxe::Render()
{
}

void PsychoAxe::PostRender()
{
}

bool PsychoAxe::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool PsychoAxe::LevelDown()
{
	return false;
}

void PsychoAxe::UpdateAxes()
{
}
