#include "framework.h"

CoinUp::CoinUp()
	:Skill(SKILL_ID::COIN,SKILL_TYPE::EXTRA,1)
{
	level_scripts.push_back("Get 100 HoloCoin.");
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
	ItemSpawner::Get()->nowCoinValue += 100;
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

void CoinUp::Enhance(float enhanceAmount)
{
	return;
}
