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

template<typename T>
T* Weapon::GetProjectTile()
{
	T* proj = nullptr;
	for (int i = 0; i < projectiles.size(); i++)// 비활성화 상태인 총알 하나를 찾아 사용
	{
		if (projectiles[i]->is_active == false)
		{
			proj = dynamic_cast<T*>(projectiles[i]);
			break;
		}
	}

	// 비활성 상태 Tear 없음 == Tear가 부족함 -> 새로 생성
	if (proj == nullptr)
	{
		proj = new T();
		projectiles.push_back(proj);
		dynamic_cast<Projectile*>(proj)->SetOwner(this);
	}

	return proj;
}