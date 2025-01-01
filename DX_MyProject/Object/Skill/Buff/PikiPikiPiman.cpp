#include "framework.h"

PikiPikiPiman::PikiPikiPiman()
    :Buff(SKILL_ID::PIKIPIK_PIMAN,3)
	,per_rate(0.0f)
{
    weight = 4;
	skillName = "PIKIPIKI PIMAN";
	levelScripts.push_back("Gain 15 Max HP. For every 6 points of total Max HP, increase damage of Main Weapon by 1%.");
	levelScripts.push_back("Gain 20 Max HP. For every 5 points of total Max HP, increase damage of Main Weapon by 1%.");
	levelScripts.push_back("Gain 25 Max HP. For every 4 points of total Max HP, increase damage of Main Weapon by 1%.");
}

PikiPikiPiman::~PikiPikiPiman()
{
}

bool PikiPikiPiman::LevelDown()
{
    return false;
}

void PikiPikiPiman::Update()
{
	if (nowLevel >= 1)
	{
		SkillManager::Get()->addMainWeaponDmgRate -= now_addRate;
		now_addRate = (player->GetMaxHP() / per_rate) / 100.0f;
		SkillManager::Get()->addMainWeaponDmgRate += now_addRate;
	}
}

void PikiPikiPiman::Render()
{
}

void PikiPikiPiman::PostRender()
{
}

bool PikiPikiPiman::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	switch (nowLevel)
	{
	case 1:
	{
		SkillManager::Get()->nowBuffList[SkillManager::Get()->buffCnt++] = this;
		player->SetMaxHP(player->GetMaxHP() + 15.0f);
		per_rate = 6.0f;
	}
	break;
	case 2:
	{
		player->SetMaxHP(player->GetMaxHP() + 5.0f);
		SkillManager::Get()->addMainWeaponDmgRate -= now_addRate;
		per_rate = 5.0f;
		now_addRate = (player->GetMaxHP() / per_rate) / 100.0f;
		SkillManager::Get()->addMainWeaponDmgRate += now_addRate;
	}
		break;
	case 3:
	{
		player->SetMaxHP(player->GetMaxHP() + 5.0f);
		SkillManager::Get()->addMainWeaponDmgRate -= now_addRate;
		per_rate = 4.0f;
		now_addRate = (player->GetMaxHP() / per_rate) / 100.0f;
		SkillManager::Get()->addMainWeaponDmgRate += now_addRate;
	}
		break;
	default:
		break;
	}
	return true;
}
