#include "framework.h"

Weapon::Weapon(SKILL_ID id,int maxLevel)
	:Skill(id,SKILL_TYPE::WEAPON,maxLevel)
{
}

Weapon::~Weapon()
{
}
