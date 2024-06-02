#include "framework.h"

NinjaHeadband::NinjaHeadband()
	:Buff(SKILL_ID::NINJA_HEADBAND,5)
{
	weight = 4;
}

NinjaHeadband::~NinjaHeadband()
{
}

bool NinjaHeadband::LevelDown()
{
	return false;
}

void NinjaHeadband::Update()
{
}

void NinjaHeadband::Render()
{
}

void NinjaHeadband::PostRender()
{
}

bool NinjaHeadband::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	switch (now_level)
	{
	case 1:
	{
		SkillManager::Get()->nowBuff_list[SkillManager::Get()->buffCnt++] = this;
	}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
	return true;
}
