#include "framework.h"

SuperChattoTime::SuperChattoTime()
	:Buff(SKILL_ID::SUPER_CHATTO_TIME,5)
{
	weight = 2;
	level_scripts.push_back("Targets drop 20% more HoloCoins. All HoloCoins are picked automatically.");
	level_scripts.push_back("Targets drop 40% more HoloCoins. All HoloCoins are picked automatically.");
	level_scripts.push_back("Targets drop 60% more HoloCoins. All HoloCoins are picked automatically.");
	level_scripts.push_back("Targets drop 80% more HoloCoins. All HoloCoins are picked automatically.");
	level_scripts.push_back("Targets drop 100% more HoloCoins. All HoloCoins are picked automatically.");
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
		ItemSpawner::Get()->isCoinAutoPick = true;
		ItemSpawner::Get()->coinValue += ItemSpawner::Get()->coinValueDefault * 0.2f;
	}
	break;
	case 2:
		ItemSpawner::Get()->coinValue += ItemSpawner::Get()->coinValueDefault * 0.2f;
		break;
	case 3:
		ItemSpawner::Get()->coinValue += ItemSpawner::Get()->coinValueDefault * 0.2f;
		break;
	case 4:
		ItemSpawner::Get()->coinValue += ItemSpawner::Get()->coinValueDefault * 0.2f;
		break;
	case 5:
		ItemSpawner::Get()->coinValue += ItemSpawner::Get()->coinValueDefault * 0.2f;
		break;
	default:
		break;
	}
	return true;
}
