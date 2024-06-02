#include "framework.h"

StudyGlasses::StudyGlasses()
	:Buff(SKILL_ID::STUDY_GLASSES,5)
{
	weight = 3;
}

StudyGlasses::~StudyGlasses()
{
}

bool StudyGlasses::LevelDown()
{
	return false;
}

void StudyGlasses::Update()
{
}

void StudyGlasses::Render()
{
}

void StudyGlasses::PostRender()
{
}

bool StudyGlasses::LevelUp()
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