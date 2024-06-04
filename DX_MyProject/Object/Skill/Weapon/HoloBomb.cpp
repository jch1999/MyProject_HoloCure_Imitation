#include "framework.h"

HoloBomb::HoloBomb()
	:Weapon(Skill::SKILL_ID::HOLO_BOMB)
{
	weight = 3;
	level_scripts.push_back("A bomb that explodes, dealing damage to all nearby targets.");
	level_scripts.push_back("Increase explosion size by 15%.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Throw 2 bombs.");
	level_scripts.push_back("Reduce the time between attacks by 20%.");
	level_scripts.push_back("Increase explosion size by 20%.");
	level_scripts.push_back("Throw 3 bombs.");
}

HoloBomb::~HoloBomb()
{
	for (auto b : bombs)
		delete b;
}

void HoloBomb::Update()
{
	if (now_level == 0)return;
	
	UpdateBomb();
	UpdateBombEffect();
}

void HoloBomb::Render()
{
	if (now_level == 0)return;
}

void HoloBomb::PostRender()
{
}

bool HoloBomb::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool HoloBomb::LevelDown()
{
	return false;
}

void HoloBomb::UpdateBomb()
{
}

void HoloBomb::UpdateBombEffect()
{
}
