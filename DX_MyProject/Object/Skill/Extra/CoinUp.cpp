#include "framework.h"

CoinUp::CoinUp()
	:Skill(SKILL_ID::COIN,SKILL_TYPE::EXTRA,1)
{
}

CoinUp::~CoinUp()
{
}

void CoinUp::Update()
{
	return;
}

void CoinUp::Render()
{
	return;
}

void CoinUp::PostRender()
{
	return;
}

bool CoinUp::LevelUp()
{
	ItemSpawner::Get()->nowCoinValue += 246;
	return true;
}

bool CoinUp::LevelDown()
{
	return false;
}

bool CoinUp::GetEnhanceAble()
{
	return false;
}

void CoinUp::Enhance(float enhanceAmount = 0.0f)
{
	return;
}
