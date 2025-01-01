#include "framework.h"

NinjaHeadband::NinjaHeadband()
	:Buff(SKILL_ID::NINJA_HEADBAND,3)
{
	weight = 4;
	skillName = "NINJA HEADBAND";
	levelScripts.push_back("Increase SPD by 20%. In addition, increase damage of Melee weapons by 5%.");
	levelScripts.push_back("Increase SPD by 30%. In addition, increase damage of Melee weapons by 10%.");
	levelScripts.push_back("Increase SPD by 40%. In addition, increase damage of Melee weapons by 15%.");
}

NinjaHeadband::~NinjaHeadband()
{
}

bool NinjaHeadband::LevelDown()
{
	return false;
}

void NinjaHeadband::Update()
{
}

void NinjaHeadband::Render()
{
}

void NinjaHeadband::PostRender()
{
}

bool NinjaHeadband::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	switch (nowLevel)
	{
	case 1:
	{
		SkillManager::Get()->nowBuffList[SkillManager::Get()->buffCnt++] = this;
		player->SetSPD(player->GetSPD() + player->GetDefaultSpd() * 0.2f);
		SkillManager::Get()->damageRateMelee += 0.05f;
	}
		break;
	case 2:
	case 3:
	{

		player->SetSPD(player->GetSPD() + player->GetDefaultSpd() * 0.1f);
		SkillManager::Get()->damageRateMelee += 0.05f;
	}
		break;
	default:
		break;
	}
	return true;
}
