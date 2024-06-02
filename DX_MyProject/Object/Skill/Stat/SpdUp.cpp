#include "framework.h"
#include "SpdUp.h"

SpdUp::SpdUp()
	:Skill(SKILL_ID::CRT, SKILL_TYPE::STAT, 1)
{
	weight = 4;
}

SpdUp::~SpdUp()
{
}

void SpdUp::Update()
{
	return;
}

void SpdUp::Render()
{
	return;
}

void SpdUp::PostRender()
{
}

bool SpdUp::LevelUp()
{
	player->SetSPD(player->GetSpeed() + player->GetDefaultSpd() * 0.12f);
	return true;
}

bool SpdUp::GetEnhanceAble()
{
	return false;
}

void SpdUp::Enhance(float enhanceAmount)
{
}

bool SpdUp::LevelDown()
{
	return false;
}
