#include "framework.h"

Buff::Buff(SKILL_ID id, int maxLevel)
	:Skill(id,SKILL_TYPE::BUFFE,maxLevel)
{
}

Buff::~Buff()
{
}

// Buff는 레벨 업 이상 강화 불가
bool Buff::Enhance()
{
	if (GetEnhanceAble())
	{
		LevelUp();
		return true;
	}
	return false;
}
