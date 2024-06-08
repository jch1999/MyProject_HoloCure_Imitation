#include "framework.h"

Weapon::Weapon(SKILL_ID id, int maxLevel)
	:Skill(id, SKILL_TYPE::WEAPON, maxLevel)
	, enhanceLevel(0),enhanceDamage(0.0f)
{
}

Weapon::~Weapon()
{
}

void Weapon::Enhance()
{
	enhanceLevel++;
	// 강화 데미지 상승 매커니즘(스킬 관련한 것도 포함해서 추후 작성)
}
