#include "framework.h"

Heal::Heal()
	:Skill(SKILL_ID::FOOD, SKILL_TYPE::EXTRA,1)
{
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

void Heal::Enhance(float enhanceAmount)
{
	return;
}
