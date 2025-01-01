#include "framework.h"

Skill::Skill(SKILL_ID id, SKILL_TYPE type,int maxLevel)
	:id(id),type(type)
	,maxLevel(maxLevel),nowLevel(0)
	,enhanceLevel(0)
	,enhanceRate(1.0f)
	,enhanceDamage(0.0f)
	,weight(0)
{
}

Skill::~Skill()
{
	
}

const int Skill::GetEnhanceCost()
{
	if(GetLevelUpAble())
		return 0;
	else
	{
		return enhanceLevel * 50;
	}
}
