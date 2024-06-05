#include "framework.h"
#include "CrtUp.h"

CrtUp::CrtUp()
	:Skill(SKILL_ID::CRT,SKILL_TYPE::STAT,1)
{
	weight = 3;
	skill_name = "CRT UP";
	level_scripts.push_back("Crt +3% Up.");
}

CrtUp::~CrtUp()
{
}

void CrtUp::Update()
{
	return;
}

void CrtUp::Render()
{
	return;
}

void CrtUp::PostRender()
{
}

bool CrtUp::LevelUp()
{
	player->SetCRT(player->GetCRT() + 3.0f);
	return true;
}

bool CrtUp::GetEnhanceAble()
{
	return false;
}

void CrtUp::Enhance(float enhanceAmount)
{
}

bool CrtUp::LevelDown()
{
	return false;
}
