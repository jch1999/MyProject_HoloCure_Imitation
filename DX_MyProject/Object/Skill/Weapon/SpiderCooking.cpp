#include "framework.h"

SpiderCooking::SpiderCooking()
	:Weapon(Skill::SKILL_ID::SPIDER_COOKING)
	,poision(nullptr)
{
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
	if (now_level == max_level)
		return false;

	now_level++;
}

bool SpiderCooking::LevelDown()
{
	return false;
}

void SpiderCooking::UpdatePoision()
{
}
