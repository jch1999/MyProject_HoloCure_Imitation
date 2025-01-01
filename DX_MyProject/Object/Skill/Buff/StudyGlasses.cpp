#include "framework.h"

StudyGlasses::StudyGlasses()
	:Buff(SKILL_ID::STUDY_GLASSES,5)
{
	weight = 3;
	skillName = "STUDY GLASSES";
	levelScripts.push_back("Increase EXP gain by 10%. On every level up, increase Weapon damage by 0.3%.");
	levelScripts.push_back("Increase EXP gain by 15%. On every level up, increase Weapon damage by 0.3%.");
	levelScripts.push_back("Increase EXP gain by 20%. On every level up, increase Weapon damage by 0.3%.");
	levelScripts.push_back("Increase EXP gain by 25%. On every level up, increase Weapon damage by 0.3%.");
	levelScripts.push_back("Increase EXP gain by 30%. On every level up, increase Weapon damage by 0.3%.");
}

StudyGlasses::~StudyGlasses()
{
}

bool StudyGlasses::LevelDown()
{
	return false;
}

void StudyGlasses::Update()
{
	return;
}

void StudyGlasses::Render()
{
	return;
}

void StudyGlasses::PostRender()
{
}

bool StudyGlasses::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	switch (nowLevel)
	{
	case 1:
	{
		SkillManager::Get()->nowBuffList[SkillManager::Get()->buffCnt++] = this;
		SkillManager::Get()->addExpRate += 0.1f;
		SkillManager::Get()->addWeaponDmgRate += 0.03f;
	}
	break;
	case 2:
	case 3:
	case 4:
	case 5:
	{
		SkillManager::Get()->addExpRate += 0.05f;
		SkillManager::Get()->addWeaponDmgRate += 0.03f;
	}
		break;
	default:
		break;
	}
	return true;
}