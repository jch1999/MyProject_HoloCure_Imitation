#include "framework.h"
#include "CrtUp.h"

CrtUp::CrtUp()
	:Skill(SKILL_ID::CRT,SKILL_TYPE::STAT,1)
{
	weight = 3;
	skillName = "CRT UP";
	levelScripts.push_back("Crt +3% Up.");
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

bool CrtUp::Enhance()
{
	return false;
}

bool CrtUp::LevelDown()
{
	return false;
}
