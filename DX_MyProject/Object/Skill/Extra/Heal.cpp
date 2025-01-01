#include "framework.h"

Heal::Heal()
	:Skill(SKILL_ID::FOOD, SKILL_TYPE::EXTRA,1)
{
	skillName = "Food";
	levelScripts.push_back("Heal +20% of HP.");
}

Heal::~Heal()
{
}

void Heal::Update()
{
}

void Heal::Render()
{
}

void Heal::PostRender()
{
}

bool Heal::LevelUp()
{
	player->ChangeHP(player->GetMaxHP() * 0.2f);
	return true;
}

bool Heal::LevelDown()
{
	return false;
}

bool Heal::GetEnhanceAble()
{
	return false;
}

bool Heal::Enhance()
{
	return false;
}
