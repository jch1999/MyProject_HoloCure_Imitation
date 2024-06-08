#include "framework.h"

ExpUp::ExpUp()
	:Skill(SKILL_ID::EXP,SKILL_TYPE::EXTRA,1)
{
}

ExpUp::~ExpUp()
{
}

void ExpUp::Update()
{
	return;
}

void ExpUp::Render()
{
	return;
}

void ExpUp::PostRender()
{
}

bool ExpUp::LevelUp()
{
	player->GetExp(player->GetMaxExp() / 10.0f);
	return true;
}

bool ExpUp::LevelDown()
{
	return false;
}

bool ExpUp::GetEnhanceAble()
{
	return false;
}

void ExpUp::Enhance()
{
	return;
}
