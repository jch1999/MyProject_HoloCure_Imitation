#include "framework.h"

SkillManager::SkillManager()
{
	weaponCnt = 0;
	buffCnt = 0;
	skill_table = {
		// DEFAULT WEAPON SKILL
		new PistolShot(),
		new PhoenixSword(),
		new PlayDice()
		// WEAPON SKILL
		
		// BUFF SKILL
	};

	// 기본 스킬 제외하고 나머지는 다 초반에 레벨 업 가능
	for (int i = 3; i < skill_table.size(); i++)
	{
		levelUpAble_list.push_back(skill_table[i]);
	}
}

SkillManager::~SkillManager()
{
	nowWeapon_list.clear();
	nowBuff_list.clear();
	levelUpAble_list.clear();
	enhanceAble_list.clear();

	for (auto s : skill_table)
		delete s;
}

void SkillManager::Update()
{
	if (player->isPause||!player->is_active)return;

	for (auto s : nowWeapon_list)
		s->Update();
	for (auto s : nowBuff_list)
		s->Update();
}

void SkillManager::Render()
{
	for (auto s : nowWeapon_list)
		s->Render();
	for (auto s : nowBuff_list)
		s->Render();
}

void SkillManager::PostRneder()
{
	for (auto s : nowWeapon_list)
		s->PostRender();
	for (auto s : nowBuff_list)
		s->PostRender();
}

const list<Skill*>& SkillManager::GetEnhaceAbleList()
{
	return enhanceAble_list;
}

const list<Skill*>& SkillManager::GetLevelUpAlbeList()
{
	levelUpAble_list.clear();
	if (weaponCnt < 6)
	{
		for (auto s : skill_table)
		{
			if (!s->GetLevelUpAble())continue;
			if (s->type == Skill::SKILL_TYPE::WEAPON)
			{
				levelUpAble_list.push_back(s);
			}
		}
	}
	if (buffCnt < 6)
	{
		for (auto s : skill_table)
		{
			if (!s->GetLevelUpAble())continue;
			if (s->type == Skill::SKILL_TYPE::BUFFE)
			{
				levelUpAble_list.push_back(s);
			}
		}
	}

	for (auto s : nowWeapon_list)
	{
		if (!s->GetLevelUpAble())continue;
		levelUpAble_list.push_back(s);
	}
	for (auto s : nowBuff_list)
	{
		if (!s->GetLevelUpAble())continue;
		levelUpAble_list.push_back(s);
	}
	return levelUpAble_list;
}

Skill* SkillManager::GetSkillByID(Skill::SKILL_ID id)
{
	for (auto s : skill_table)
	{
		if (s->id == id)
			return s;
	}
}

void SkillManager::SetPlayer(Player* p)
{
	player = p;
	// 플레이어 ID에 따라 다른 기본 스킬 부여
	switch (player->player_id)
	{
	case Player::PLAYER_ID::WATSON:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]);
		skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]->SetPlayer(player);
		enhanceAble_list.push_back(skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]);
		weaponCnt++;
	}
		break; 
	case Player::PLAYER_ID::KIARA:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
		skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->SetPlayer(player);
		enhanceAble_list.push_back(skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
		weaponCnt++;
	}
			break;
	case Player::PLAYER_ID::BAELZ:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PLAY_DICE]);
		skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->SetPlayer(player);
		enhanceAble_list.push_back(skill_table[(int)Skill::SKILL_ID::PLAY_DICE]);
		weaponCnt++;
	}
		break;
	}
}

void SkillManager::LevelUp(Skill::SKILL_ID id)
{
	for (auto s : levelUpAble_list)
	{
		if (s->id == id)
		{
			s->LevelUp();
			if (!s->GetLevelUpAble()) // 최대 레벨 도달
			{
				if (s->type == Skill::SKILL_TYPE::BUFFE)
					enhanceAble_list.remove(s);
			}
			else
			{
				if (s->GetLevel() == 1)
				{
					enhanceAble_list.push_back(s);
					
					switch (s->type)
					{
					case Skill::SKILL_TYPE::BUFFE:
					{
						nowBuff_list.push_back(s);
						s->SetPlayer(player);
						buffCnt++;
					}
						break;
					case Skill::SKILL_TYPE::WEAPON:
					{
						nowWeapon_list.push_back(s);
						s->SetPlayer(player);
						weaponCnt++;
					}
					break;
					default:
						break;
					}
				}
			}
			return;
		}
	}
}

void SkillManager::Enhance(Skill::SKILL_ID id, float enhanceAmount)
{
	for (auto s : enhanceAble_list)
	{
		if (s->id == id)
		{
			if (s->GetLevelUpAble())
			{
				LevelUp(id);
			}
			else if (!s->GetEnhanceAble())
			{
				enhanceAble_list.remove(s);
			}
			else
			{
				s->Enhance(enhanceAmount);
			}
		}
	}
}
