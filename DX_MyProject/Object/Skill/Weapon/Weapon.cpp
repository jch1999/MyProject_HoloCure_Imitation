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
	if (GetLevelUpAble())
	{
		LevelUp();
	}
	else if (GetEnhanceAble())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand <= enhance_rate)
		{
			enhance_rate -= 0.1f;
			if (enhance_rate < 0.1f)
				enhance_rate = 0.1f;
			ItemSpawner::Get()->nowCoinValue -= enhance_level * 50.0f;
			enhanceLevel++;
			enhanceDamage += ItemSpawner::Get()->enhanceDmg;
		}
	}
}
