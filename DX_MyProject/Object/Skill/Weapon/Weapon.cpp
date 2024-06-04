#include "framework.h"

Weapon::Weapon(SKILL_ID id, int maxLevel)
	:Skill(id, SKILL_TYPE::WEAPON, maxLevel)
	, enhanceLevel(0),enhanceDamage(0.0f)
{
}

Weapon::~Weapon()
{
}
