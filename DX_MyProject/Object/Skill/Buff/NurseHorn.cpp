#include "framework.h"

NurseHorn::NurseHorn()
    :Buff(SKILL_ID::NURSE_HORN,5)
{
    weight = 3;
}

NurseHorn::~NurseHorn()
{
}

bool NurseHorn::LevelDown()
{
    return false;
}

void NurseHorn::Update()
{
}

void NurseHorn::Render()
{
}

void NurseHorn::PostRender()
{
}

bool NurseHorn::LevelUp()
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
