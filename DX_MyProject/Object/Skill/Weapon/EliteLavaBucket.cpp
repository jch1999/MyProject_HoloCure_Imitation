#include "framework.h"

EliteLavaBucket::EliteLavaBucket()
	:Weapon(Skill::SKILL_ID::ELITE_LAVA_BUCKET)
{
	weight = 3;
	level_scripts.push_back("Drop lava on the ground, burning targets slowly.");
	level_scripts.push_back("Increase lava area by 20%.");
	level_scripts.push_back("Throw 2 lava buckets.");
	level_scripts.push_back("Increase damage by 30% and increase duration of lava by 1 second");
	level_scripts.push_back("Increase damage by 30%");
	level_scripts.push_back("Throw 3 lava buckets");
	level_scripts.push_back("Throw 4 lava buckets and increase lava size by 20%");
}

EliteLavaBucket::~EliteLavaBucket()
{
	for (auto p : buckets)
		delete p;
}

void EliteLavaBucket::Update()
{
	if (now_level == 0)return;

	UpdateBuckets();
}

void EliteLavaBucket::Render()
{
	if (now_level == 0)return;

	for (auto p : buckets)
		p->Render();
}

void EliteLavaBucket::PostRender()
{
}

bool EliteLavaBucket::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool EliteLavaBucket::LevelDown()
{
	return false;
}

void EliteLavaBucket::UpdateBuckets()
{
}
