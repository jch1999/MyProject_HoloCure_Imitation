#include "framework.h"
#include "CrtUp.h"

CrtUp::CrtUp()
	:Skill(SKILL_ID::CRT,SKILL_TYPE::STAT,1)
{
	weight = 3;
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
	player->SetCRT(player->GetCRT() + player->GetDefaultCrt() * 0.03f);
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
