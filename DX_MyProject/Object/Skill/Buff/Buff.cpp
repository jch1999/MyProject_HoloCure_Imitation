#include "framework.h"

Buff::Buff(SKILL_ID id, int maxLevel)
	:Skill(id,SKILL_TYPE::BUFFE,maxLevel)
{
	type = SKILL_TYPE::BUFFE;
}

Buff::~Buff()
{
}

// Buff�� ���� �� �̻� ��ȭ �Ұ�
bool Buff::Enhance()
{
	if (GetEnhanceAble())
	{
		LevelUp();
		return true;
	}
	return false;
}
