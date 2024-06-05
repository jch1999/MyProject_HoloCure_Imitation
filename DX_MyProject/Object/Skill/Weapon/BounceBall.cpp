#include "framework.h"

BounceBall::BounceBall()
	:Weapon(SKILL_ID::BOUNCE_BALL)
{
	weight = 4;
	skill_name = "BOUNCE BALL";
	level_scripts.push_back("Drops a falling bounce ball on a random target. Size of ball varies between characters.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Drop 2 balls.");
	level_scripts.push_back("Gain knockback effect. The strength of knockback varies from character.");
	level_scripts.push_back("Drop 3 balls.");
	level_scripts.push_back("Reduce the time between attacks by 15%.");
	level_scripts.push_back("Increase damage by 30% and drop 4 balls.");
}

BounceBall::~BounceBall()
{
	for (auto p : balls)
		delete p;
}

void BounceBall::UpdateBalls()
{
}

bool BounceBall::LevelDown()
{
	return false;
}

void BounceBall::Update()
{
}

void BounceBall::Render()
{
}

void BounceBall::PostRender()
{
}

bool BounceBall::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}
