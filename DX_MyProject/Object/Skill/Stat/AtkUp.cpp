#include "framework.h"
#include "AtkUp.h"

AtkUp::AtkUp()
	:Skill(SKILL_ID::ATK, SKILL_TYPE::STAT, 1)
{
	weight = 3;
	skillName = "ATK UP";
	levelScripts.push_back("ATK +10% Up.");
}

AtkUp::~AtkUp()
{
}

void AtkUp::Update()
{
	return;
}

void AtkUp::Render()
{
	return;
}

void AtkUp::PostRender()
{
}

bool AtkUp::LevelUp()
{
	player->SetATK(player->GetATK() + player->GetDefaultAtk() * 0.08f);
	return true;
}

bool AtkUp::LevelDown()
{
	return false;
}

bool AtkUp::GetEnhanceAble()
{
	return false;
}

bool AtkUp::Enhance()
{
	return false;
}
