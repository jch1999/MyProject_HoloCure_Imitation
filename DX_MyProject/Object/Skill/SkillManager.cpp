#include "framework.h"

SkillManager::SkillManager()
	:total_weight_W(0),total_weight_B(0),total_weight_S(0),total_weight_E(0)
{
	weaponCnt = 0;
	buffCnt = 0;
	skill_table = {
		// DEFAULT WEAPON SKILL
		new PistolShot(),
		new PhoenixSword(),
		new PlayDice(),
		// WEAPON SKILL
		new HoloBomb(),
		new EliteLavaBucket(),
		new PsychoAxe(),
		new SpiderCooking(),
		// BUFF SKILL

		// STAT SKILL
		new MaxHpUp(),
		new AtkUp(),
		new SpdUp(),
		new CrtUp(),
		new PickRangeUp(),
		// EXTRA SKILL
		new ExpUp(),
		new Heal(),
		new CoinUp(),
	};

	player = EnemySpawner::Get()->GetPlayer();
	switch (player->player_id)
	{
	case Player::PLAYER_ID::BAELZ:
		SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PLAY_DICE)->LevelUp();
		break;
	case Player::PLAYER_ID::KIARA:
		SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PHOENIX_SWORD)->LevelUp();
		break;
	case Player::PLAYER_ID::WATSON:
		SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PISTOL_SHOT)->LevelUp();
		break;
	}
}

SkillManager::~SkillManager()
{
	nowWeapon_list.clear();
	nowBuff_list.clear();
	levelUpAble_list.clear();

	for (auto s : skill_table)
		delete s;
}

void SkillManager::Update()
{
	if (isPause||!player->is_active)return;

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
		weaponCnt++;
	}
		break; 
	case Player::PLAYER_ID::KIARA:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
		skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->SetPlayer(player);
		weaponCnt++;
	}
			break;
	case Player::PLAYER_ID::BAELZ:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PLAY_DICE]);
		skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->SetPlayer(player);
		weaponCnt++;
	}
		break;
	}

	Update_LevelUpAlbeList();
}

void SkillManager::Update_LevelUpAlbeList()
{
	// 2(stat), 3(extra)은 업데이트할 필요 없음
	levelUpAble_list[0].clear();
	levelUpAble_list[1].clear();

	switch (player->player_id)
	{
	case Player::PLAYER_ID::WATSON:
		if (skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]->GetLevelUpAble())
		{
			levelUpAble_list[0].push_back(skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]);
		}
		break;
	case Player::PLAYER_ID::KIARA:
		if (skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->GetLevelUpAble())
		{
			levelUpAble_list[0].push_back(skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
		}
		break;
	case Player::PLAYER_ID::BAELZ:
		if (skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->GetLevelUpAble())
		{
			levelUpAble_list[0].push_back(skill_table[(int)Skill::SKILL_ID::PLAY_DICE]);
		}
		break;
	}

	if (weaponCnt == 6)
	{
		for (int i = 0; i < 6; i++)
		{
			if (nowWeapon_list[i]->GetLevelUpAble())
			{
				levelUpAble_list[0].push_back(skill_table[(int)nowWeapon_list[i]->id]);
			}
		}
	}
	else
	{
		int startIdx = (int)Skill::SKILL_ID::HOLO_BOMB;
		int endIdx= (int)Skill::SKILL_ID::SPIDER_COOKING;
		for (int i = startIdx; i <= endIdx; i++)
		{
			if (skill_table[i]->type == Skill::SKILL_TYPE::WEAPON)
			{
				if (skill_table[i]->GetLevelUpAble())
				{
					levelUpAble_list[0].push_back(skill_table[i]);
				}
			}
		}
	}

	if (buffCnt == 6)
	{
		for (int i = 0; i < 6; i++)
		{
			if (nowBuff_list[i]->GetLevelUpAble())
			{
				levelUpAble_list[1].push_back(skill_table[(int)nowBuff_list[i]->id]);
			}
		}
	}
	else
	{
		int startIdx = (int)Skill::SKILL_ID::NURSE_HORN;
		int endIdx = (int)Skill::SKILL_ID::NINJA_HEADBAND;
		for (int i = startIdx; i <= endIdx; i++)
		{
			if (skill_table[i]->type == Skill::SKILL_TYPE::BUFFE)
			{
				if (skill_table[i]->GetLevelUpAble())
				{
					levelUpAble_list[1].push_back(skill_table[i]);
				}
			}
		}
	}
}

int SkillManager::GetLevelUpSkillID()
{
	int skill_id=-1;
	if (levelUpAble_list[0].size() + levelUpAble_list[1].size() < 4)
	{
		int rand = Random::Get()->GetRandomInt(0, 2);
		skill_id = (int)Skill::SKILL_ID::MAX_HP + rand;
	}
	else
	{
		int rand = Random::Get()->GetRandomInt(0, 19);
		if (rand < 11)
		{
			if (levelUpAble_list[0].size() == 0)
			{

			}
			else
			{

			}
		}
		else if (rand < 18)
		{

		}
		else
		{

		}
	}

	return skill_id;
}

void SkillManager::LevelUp(Skill::SKILL_ID id)
{
}

void SkillManager::Enhance(Skill::SKILL_ID id, float enhanceAmount)
{

}
