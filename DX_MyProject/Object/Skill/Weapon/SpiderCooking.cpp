#include "framework.h"

SpiderCooking::SpiderCooking()
	:Weapon(Skill::SKILL_ID::SPIDER_COOKING)
	,poison(nullptr)
{
	weight = 4;
	skill_name = "SPIDER COOKING";
	level_scripts.push_back("Create an area of miasma around, dealing slow damage to enemies inside.");
	level_scripts.push_back("Increase area by 15%.");
	level_scripts.push_back("Increase damage by 30%.");
	level_scripts.push_back("Increase area by 25%.");
	level_scripts.push_back("Increase frequency of hits by 20%.");
	level_scripts.push_back("Increase damage by 60%.");
	level_scripts.push_back("Add small knockback on hit.(not Implemented)");

	minDamage_table = { 0, 7.0f, 7.0f,10.0f, 10.0f, 10.0f, 12.0f,12.0f };
	maxDamage_table = { 0, 11.0f, 11.0f,14.0f, 14.0f, 14.0f, 16.0f,16.0f };
	colliderIdx_table = { 0, 0, 1, 1, 2, 2, 2, 2 };
	hitCooldown_table = { 0, 0.75f, 0.75f, 0.75f, 0.75f, 0.6f, 0.6f, 0.6f };
	hiLimit_table = { 0,1,1,1,1,1,1 };

	poison = new PoisonArea();

	now_skill_delay = 0.0f;
	playTime_table.push_back(1.0f);
	play_time = 0.0f;
	enhanceDamage = 0.0f;
}

SpiderCooking::~SpiderCooking()
{
	delete poison;
}

void SpiderCooking::Update()
{
	if (now_level == 0)return;

	UpdatePoision();
}

void SpiderCooking::Render()
{
	if (now_level == 0)return;

	poison->Render();
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
	poison->pos = player->pos;
	poison->Update();
}
