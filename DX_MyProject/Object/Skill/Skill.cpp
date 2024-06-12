#include "framework.h"

Skill::Skill(SKILL_ID id, SKILL_TYPE type,int maxLevel)
	:id(id),type(type),max_level(maxLevel),now_level(0),enhance_level(0)
{
}

Skill::~Skill()
{
	
}

int Skill::GetEnhanceCost()
{
	if(GetLevelUpAble())
		return 0;
	else
	{
		return enhance_level * 50;
	}
}
