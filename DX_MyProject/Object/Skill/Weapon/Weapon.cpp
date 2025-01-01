#include "framework.h"

Weapon::Weapon(SKILL_ID id, int maxLevel)
	:Skill(id, SKILL_TYPE::WEAPON, maxLevel)
{
	type = SKILL_TYPE::WEAPON;
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
		if (rand <= enhanceRate)
		{
			enhanceRate -= 0.1f;
			if (enhanceRate < 0.1f)
			{
				enhanceRate = 0.1f;
			}

			if (ItemSpawner::Get()->nowCoinValue - enhanceLevel * 50.0f < 0.0f)
			{
				ItemSpawner::Get()->nowCoinValue = 0.0f;
			}
			else
			{
				ItemSpawner::Get()->nowCoinValue -= enhanceLevel * 50.0f;
			}

			enhanceLevel++;
			enhanceDamage += ItemSpawner::Get()->enhanceDmg;
			return true;
		}
	}
	return false;
}