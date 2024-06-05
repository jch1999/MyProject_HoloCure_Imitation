#include "framework.h"

SkillManager::SkillManager()
	:total_weight_W(0),total_weight_B(0),total_weight_S(0),total_weight_E(0)
	, isHealDoubled(false) ,nurseHron_active(false)
	, add_expRate(0.0f),add_MainWeapon_dmgRate(0.0f)
	, damageRate_Melee(0.0f),damageRate_Shot(0.0f),damageRate_Range(0.0f)
{
	weaponCnt = 0;
	buffCnt = 0;
	nowWeapon_list.resize(6);
	nowBuff_list.resize(6);

	skill_table = {
		// DEFAULT WEAPON SKILL
		new PistolShot(),
		new PhoenixSword(),
		new PlayDice(),
		// WEAPON SKILL
		new HoloBomb(),
		new EliteLavaBucket(),
		new PsychoAxe(),
		new BounceBall(),
		new CEOTear(),
		new SpiderCooking(),
		// BUFF SKILL
		new NurseHorn(),
		new FullMeal(),
		new PikiPikiPiman(),
		new StudyGlasses(),
		new SuperChattoTime(),
		new BlackSmithGear(),
		new NinjaHeadband(),
		// STAT SKILL
		new MaxHpUp(),
		new AtkUp(),
		new SpdUp(),
		new CrtUp(),
		new PickRangeUp(),
		// EXTRA SKILL
		new CoinUp(),
		new Heal(), // FOOD에 해당
		new ExpUp(),
	};

	for (int i = 0; i < 4; i++)
	{
		vector<Skill*> list;
		levelUpAble_list.push_back(list);
	}
	for (int i = 0; i < 5; i++)
	{
		int idx = (int)Skill::SKILL_ID::MAX_HP + i;
		levelUpAble_list[2].push_back(skill_table[idx]);
		total_weight_S += skill_table[idx]->weight;
	}
	for (int i = 0; i < 2; i++)
	{
		int idx = (int)Skill::SKILL_ID::COIN + i;
		levelUpAble_list[3].push_back(skill_table[idx]);
		total_weight_E += skill_table[idx]->weight;
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
	{
		if(s!=nullptr)
			s->Update();
	}
	for (auto s : nowBuff_list)
	{
		if (s != nullptr)
			s->Update();
	}
}

void SkillManager::Render()
{
	for (auto s : nowWeapon_list)
	{
		if (s != nullptr)
			s->Render();
	}
	for (auto s : nowBuff_list)
	{
		if (s != nullptr)
			s->Render();
	}
}

void SkillManager::PostRneder()
{
	ImGui::Text("nowWeaponCnt : %d", weaponCnt);
	ImGui::Text("nowBuffCnt : %d", buffCnt);
	for (auto s : nowWeapon_list)
	{
		if (s != nullptr)
			s->PostRender();
	}
	for (auto s : nowBuff_list)
	{
		if (s != nullptr)
			s->PostRender();
	}
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
	}
		break; 
	case Player::PLAYER_ID::KIARA:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
		skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->SetPlayer(player);
	}
			break;
	case Player::PLAYER_ID::BAELZ:
	{
		nowWeapon_list.push_back(skill_table[(int)Skill::SKILL_ID::PLAY_DICE]);
		skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->LevelUp();
		skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->SetPlayer(player);
	}
		break;
	default:
		break;
	}
	for (auto s : skill_table)
		s->SetPlayer(player);

	Update_LevelUpAlbeList();
}

void SkillManager::Update_LevelUpAlbeList()
{
	// 2(stat), 3(extra)은 업데이트할 필요 없음
	levelUpAble_list[0].clear();
	levelUpAble_list[1].clear();
	total_weight_W = 0;
	total_weight_B = 0;

	switch (player->player_id)
	{
	case Player::PLAYER_ID::WATSON:
		if (skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]->GetLevelUpAble())
		{
			levelUpAble_list[0].push_back(skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]);
			total_weight_W += skill_table[(int)Skill::SKILL_ID::PISTOL_SHOT]->weight;
		}
		break;
	case Player::PLAYER_ID::KIARA:
		if (skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->GetLevelUpAble())
		{
			levelUpAble_list[0].push_back(skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
			total_weight_W += skill_table[(int)Skill::SKILL_ID::PHOENIX_SWORD]->weight;
		}
		break;
	case Player::PLAYER_ID::BAELZ:
		if (skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->GetLevelUpAble())
		{
			levelUpAble_list[0].push_back(skill_table[(int)Skill::SKILL_ID::PLAY_DICE]);
			total_weight_W += skill_table[(int)Skill::SKILL_ID::PLAY_DICE]->weight;
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
				total_weight_W += skill_table[(int)nowWeapon_list[i]->id]->weight;
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
					total_weight_W += skill_table[i]->weight;
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
				total_weight_B += skill_table[(int)nowBuff_list[i]->id]->weight;
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
					total_weight_B += skill_table[i]->weight;
				}
			}
		}
	}
}

int SkillManager::GetLevelUpSkillID()
{
	Update_LevelUpAlbeList();
	int skill_id = -1;
	int rand = Random::Get()->GetRandomInt(0, 19);
	if (rand < 10)
	{
		skill_id = GetLevelUpSkillID_W();
	}
	else if(rand<19)
	{
		skill_id = GetLevelUpSkillID_B();
	}
	else
	{
		skill_id = GetLevelUpSkillID_S();
	}

	return skill_id;
}

int SkillManager::GetLevelUpSkillID_W()
{
	if (levelUpAble_list[0].size() != 0)
	{
		int target_weight = Random::Get()->GetRandomInt(1, total_weight_W);
		int now_weight = 0;
		for (int i = 0; i < levelUpAble_list[0].size(); i++)
		{
			now_weight += levelUpAble_list[0][i]->weight;
			if (now_weight >= target_weight)
			{
				return (int)levelUpAble_list[0][i]->id;
			}
		}
	}
	else
	{
		return GetLevelUpSkillID_B();
	}
}

int SkillManager::GetLevelUpSkillID_B()
{
	if (levelUpAble_list[1].size() != 0)
	{
		int target_weight = Random::Get()->GetRandomInt(1, total_weight_B);
		int now_weight = 0;
		for (int i = 0; i < levelUpAble_list[1].size(); i++)
		{
			now_weight += levelUpAble_list[1][i]->weight;
			if (now_weight >= target_weight)
			{
				return (int)levelUpAble_list[1][i]->id;
			}
		}
	}
	else
	{
		return GetLevelUpSkillID_S();
	}
}

int SkillManager::GetLevelUpSkillID_S()
{
	int target_weight = Random::Get()->GetRandomInt(1, total_weight_S);
	int now_weight = 0;
	for (int i = 0; i < levelUpAble_list[2].size(); i++)
	{
		now_weight += levelUpAble_list[2][i]->weight;
		if (now_weight >= target_weight)
		{
			return (int)levelUpAble_list[2][i]->id;
		}
	}
}

int SkillManager::GetLevelUpSkillID_E()
{
	int skill_idx = Random::Get()->GetRandomInt(0, levelUpAble_list[3].size() - 1);
	return (int)(levelUpAble_list[3][skill_idx]->id);
}

void SkillManager::LevelUp(Skill::SKILL_ID id)
{
	
}

void SkillManager::Enhance(Skill::SKILL_ID id, float enhanceAmount)
{

}
