#include "framework.h"
#include "SpdUp.h"

SpdUp::SpdUp()
	:Skill(SKILL_ID::SPD, SKILL_TYPE::STAT, 1)
{
	weight = 4;
	skill_name = "SPD UP";
	level_scripts.push_back("SPD +12% Up.");
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
	player->SetSPD(player->GetSPD() + player->GetDefaultSpd() * 0.12f);
	return true;
}

bool SpdUp::GetEnhanceAble()
{
	return false;
}

bool SpdUp::Enhance()
{
	return false;
}

bool SpdUp::LevelDown()
{
	return false;
}
