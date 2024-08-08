#include "framework.h"

PsychoAxe::PsychoAxe()
	:Weapon(Skill::SKILL_ID::PSYCHO_AXE)
{
	weight = 3;
	skill_name = "PSYCHO AXE";
	level_scripts.push_back("Throw an axe that spirals outward from the player.");
	level_scripts.push_back("Increase size of axe by 20%. Increase damage of axe by 20%.");
	level_scripts.push_back("Reduce delay between attacks by 20%.");
	level_scripts.push_back("Increase damage by 33%, and size by 20%.");
	level_scripts.push_back("Remove hit limit, and lasts 1 second longer.");
	level_scripts.push_back("Increase attack size by 50%.");
	level_scripts.push_back("Increase damage by 50%.");

	skillDelay_table = { 0,2.0f, 2.0f, 2.0f, 2.0f, 1.6f,1.6f,1.6f };
	minDamage_table = { 0,10.0f,14.0f,14.0f,19.0f,19.0f,19.0f,28.0f };
	maxDamage_table = { 0,14.0f,18.0f,18.0f,23.0f,23.0f,23.0f,34.0f };
	colliderIdx_table = { 0, 0, 1, 1, 2, 2, 3, 3 };
	projCnt_talbe = { 0,1,1,2,2,3,3,4 };
	proj_spd = 10.0f;
	hitLimit_table = { 0,1,1,1,1,1,1,1 };
	hitCooldown = 0.83f;

	weapon_type = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;
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
	for (auto axe : projectiles)
	{
		axe->Update();
	}
}
