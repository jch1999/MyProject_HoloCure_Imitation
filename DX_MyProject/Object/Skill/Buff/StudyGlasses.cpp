#include "framework.h"

StudyGlasses::StudyGlasses()
	:Buff(SKILL_ID::STUDY_GLASSES,5)
{
	weight = 3;
	skill_name = "STUDY GLASSES";
	level_scripts.push_back("Increase EXP gain by 10%. On every level up, increase Weapon damage by 0.3%.");
	level_scripts.push_back("Increase EXP gain by 15%. On every level up, increase Weapon damage by 0.3%.");
	level_scripts.push_back("Increase EXP gain by 20%. On every level up, increase Weapon damage by 0.3%.");
	level_scripts.push_back("Increase EXP gain by 25%. On every level up, increase Weapon damage by 0.3%.");
	level_scripts.push_back("Increase EXP gain by 30%. On every level up, increase Weapon damage by 0.3%.");
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
	if (now_level == max_level)return false;

	now_level++;
	switch (now_level)
	{
	case 1:
	{
		SkillManager::Get()->nowBuff_list[SkillManager::Get()->buffCnt++] = this;
		SkillManager::Get()->add_expRate += 0.1f;
		SkillManager::Get()->add_Weapon_dmgRate += 0.03f;
	}
	break;
	case 2:
	case 3:
	case 4:
	case 5:
	{
		SkillManager::Get()->add_expRate += 0.05f;
		SkillManager::Get()->add_Weapon_dmgRate += 0.03f;
	}
		break;
	default:
		break;
	}
	return true;
}