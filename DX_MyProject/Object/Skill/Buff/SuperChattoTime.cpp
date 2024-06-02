#include "framework.h"

SuperChattoTime::SuperChattoTime()
	:Buff(SKILL_ID::SUPER_CHATTO_TIME,5)
{
	weight = 2;
}

SuperChattoTime::~SuperChattoTime()
{
}

bool SuperChattoTime::LevelDown()
{
	return false;
}

void SuperChattoTime::Update()
{
}

void SuperChattoTime::Render()
{
}

void SuperChattoTime::PostRender()
{
}

bool SuperChattoTime::LevelUp()
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
