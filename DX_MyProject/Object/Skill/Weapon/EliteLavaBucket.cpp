#include "framework.h"

EliteLavaBucket::EliteLavaBucket()
	:Weapon(Skill::SKILL_ID::ELITE_LAVA_BUCKET)
{
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
	if(now_level==max_level)
		return false;

	now_level++;
}

bool EliteLavaBucket::LevelDown()
{
	return false;
}

void EliteLavaBucket::UpdateBuckets()
{
}
