#include "framework.h"

BounceBall::BounceBall()
	:Weapon(SKILL_ID::BOUNCE_BALL)
{
	weight = 4;
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
