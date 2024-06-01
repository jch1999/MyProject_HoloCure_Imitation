#include "framework.h"
#include "AtkUp.h"

AtkUp::AtkUp()
	:Skill(SKILL_ID::ATK, SKILL_TYPE::STAT, 1)
{
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
	player->SetATK(player->GetATK(4) + player->GetDefaultAtk() * 0.08f);
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

void AtkUp::Enhance(float enhanceAmount = 0.0f)
{
	return;
}
