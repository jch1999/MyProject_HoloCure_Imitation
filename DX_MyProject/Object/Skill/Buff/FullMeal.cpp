#include "framework.h"

FullMeal::FullMeal()
    :Buff(SKILL_ID::FULL_MEAL,1)
{
    weight = 1;
    skillName = "FULL MEAL";
    levelScripts.push_back("All healing is doubled.");
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
    if(nowLevel == maxLevel)return false;

    nowLevel++;
    SkillManager::Get()->nowBuffList[SkillManager::Get()->buffCnt++] = this;
    SkillManager::Get()->isHealDoubled = true;
    return true;
}
