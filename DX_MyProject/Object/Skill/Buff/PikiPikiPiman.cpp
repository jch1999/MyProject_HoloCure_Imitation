#include "framework.h"

PikiPikiPiman::PikiPikiPiman()
    :Buff(SKILL_ID::PIKIPIK_PIMAN,3)
	,per_rate(0.0f)
{
    weight = 4;
	skill_name = "PIKIPIKI PIMAN";
	level_scripts.push_back("Gain 15 Max HP. For every 6 points of total Max HP, increase damage of Main Weapon by 1%.");
	level_scripts.push_back("Gain 20 Max HP. For every 5 points of total Max HP, increase damage of Main Weapon by 1%.");
	level_scripts.push_back("Gain 25 Max HP. For every 4 points of total Max HP, increase damage of Main Weapon by 1%.");
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
	if (now_level >= 1)
	{
		SkillManager::Get()->add_MainWeapon_dmgRate -= now_addRate;
		now_addRate = (player->GetMaxHP() / per_rate);
		SkillManager::Get()->add_MainWeapon_dmgRate += now_addRate;
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
	if (now_level == max_level)return false;

	now_level++;
	switch (now_level)
	{
	case 1:
	{
		SkillManager::Get()->nowBuff_list[SkillManager::Get()->buffCnt++] = this;
		player->SetMaxHP(player->GetMaxHP() + 15.0f);
		per_rate = 6.0f;
	}
	break;
	case 2:
	{
		player->SetMaxHP(player->GetMaxHP() + 5.0f);
		SkillManager::Get()->add_MainWeapon_dmgRate -= now_addRate;
		per_rate = 5.0f;
		now_addRate = (player->GetMaxHP() / per_rate);
		SkillManager::Get()->add_MainWeapon_dmgRate += now_addRate;
	}
		break;
	case 3:
	{
		player->SetMaxHP(player->GetMaxHP() + 5.0f);
		SkillManager::Get()->add_MainWeapon_dmgRate -= now_addRate;
		per_rate = 4.0f;
		now_addRate = (player->GetMaxHP() / per_rate);
		SkillManager::Get()->add_MainWeapon_dmgRate += now_addRate;
	}
		break;
	default:
		break;
	}
	return true;
}
