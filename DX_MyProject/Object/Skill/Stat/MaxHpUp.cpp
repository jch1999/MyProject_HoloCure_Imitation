#include "framework.h"
#include "MaxHpUp.h"

MaxHpUp::MaxHpUp()
	:Skill(SKILL_ID::MAX_HP, SKILL_TYPE::STAT, 1)
{
	weight = 2;
	level_scripts.push_back("Max HP +10% Up.");
}

MaxHpUp::~MaxHpUp()
{
}

void MaxHpUp::Update()
{
	return;
}

void MaxHpUp::Render()
{
	return;
}

void MaxHpUp::PostRender()
{
}

bool MaxHpUp::LevelUp()
{
	float newMaxHp = player->GetMaxHP() + player->GetDefaultMaxHP() * 0.1f;
	player->SetMaxHP(newMaxHp);
	return true;
}

bool MaxHpUp::LevelDown()
{
	return false;
}

bool MaxHpUp::GetEnhanceAble()
{
	return false;
}

void MaxHpUp::Enhance(float enhanceAmount)
{
	return;
}
