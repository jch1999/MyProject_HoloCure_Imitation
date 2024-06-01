#include "framework.h"

HoloBomb::HoloBomb()
	:Weapon(Skill::SKILL_ID::HOLO_BOMB)
{
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
	if (now_level == max_level)
		return false;

	now_level++;
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
