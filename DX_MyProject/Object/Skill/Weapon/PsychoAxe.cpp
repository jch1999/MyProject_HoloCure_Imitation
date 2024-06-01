#include "framework.h"

PsychoAxe::PsychoAxe()
	:Weapon(Skill::SKILL_ID::PSYCHO_AXE)
{
}

PsychoAxe::~PsychoAxe()
{
}

void PsychoAxe::Update()
{
	if (now_level == 0)return;

	UpdateAxes();
}

void PsychoAxe::Render()
{
}

void PsychoAxe::PostRender()
{
}

bool PsychoAxe::LevelUp()
{
	if (now_level == max_level)
		return false;

	now_level++;
}

bool PsychoAxe::LevelDown()
{
	return false;
}

void PsychoAxe::UpdateAxes()
{
}
