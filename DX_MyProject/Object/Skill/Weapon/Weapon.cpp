#include "framework.h"

Weapon::Weapon(SKILL_ID id, int maxLevel)
	:Skill(id, SKILL_TYPE::WEAPON, maxLevel)
{
}

Weapon::~Weapon()
{
	for (auto p : projectiles)
		delete p;
}

bool Weapon::Enhance()
{
	if (GetLevelUpAble())
	{
		LevelUp();
		return true;
	}
	else if (GetEnhanceAble())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand <= enhance_rate)
		{
			enhance_rate -= 0.1f;
			if (enhance_rate < 0.1f)
				enhance_rate = 0.1f;
			if (ItemSpawner::Get()->nowCoinValue - enhance_level * 50.0f < 0.0f)
				ItemSpawner::Get()->nowCoinValue = 0.0f;
			else
				ItemSpawner::Get()->nowCoinValue -= enhance_level * 50.0f;
			enhance_level++;
			enhanceDamage += ItemSpawner::Get()->enhanceDmg;
			return true;
		}
	}
	return false;
}
