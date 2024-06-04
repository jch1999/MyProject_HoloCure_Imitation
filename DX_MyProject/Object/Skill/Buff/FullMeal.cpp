#include "framework.h"

FullMeal::FullMeal()
    :Buff(SKILL_ID::FULL_MEAL,1)
{
    weight = 1;
    level_scripts.push_back("All healing is doubled.");
}

FullMeal::~FullMeal()
{
}

bool FullMeal::LevelDown()
{
    return false;
}

void FullMeal::Update()
{
}

void FullMeal::Render()
{
}

void FullMeal::PostRender()
{
}

bool FullMeal::LevelUp()
{
    if(now_level == max_level)return false;

    now_level++;
    SkillManager::Get()->nowBuff_list[SkillManager::Get()->buffCnt++] = this;
    SkillManager::Get()->isHealDoubled = true;
    return true;
}
