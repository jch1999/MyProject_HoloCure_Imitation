#include "framework.h"

SkillManager::SkillManager()
	:totalWeightW(0),totalWeightB(0),totalWeightS(0),totalWeightE(0)
	, isHealDoubled(false) ,nurseHronActive(false)
	, addExpRate(0.0f),addMainWeaponDmgRate(0.0f)
	, damageRateMelee(0.0f),damageRateShot(0.0f),damageRateRange(0.0f)
{
	weaponCnt = 0;
	buffCnt = 0;
	nowWeaponList.resize(6);
	nowBuffList.resize(6);

	skillTable = {
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
		levelUpAbleList.push_back(list);
	}
	for (int i = 0; i < 5; i++)
	{
		int idx = (int)Skill::SKILL_ID::MAX_HP + i;
		levelUpAbleList[2].push_back(skillTable[idx]);
		totalWeightS += skillTable[idx]->weight;
	}
	for (int i = 0; i < 2; i++)
	{
		int idx = (int)Skill::SKILL_ID::COIN + i;
		levelUpAbleList[3].push_back(skillTable[idx]);
		totalWeightE += skillTable[idx]->weight;
	}
}

SkillManager::~SkillManager()
{
	nowWeaponList.clear();
	nowBuffList.clear();
	levelUpAbleList.clear();

	for (auto s : skillTable)
		delete s;
}

void SkillManager::Update()
{
	if (isPause||!player->is_active)return;

	for (auto s : nowWeaponList)
	{
		if(s!=nullptr)
			s->Update();
	}
	for (auto s : nowBuffList)
	{
		if (s != nullptr)
			s->Update();
	}
}

void SkillManager::Render()
{
	for (auto s : nowWeaponList)
	{
		if (s != nullptr)
			s->Render();
	}
	for (auto s : nowBuffList)
	{
		if (s != nullptr)
			s->Render();
	}
}

void SkillManager::PostRneder()
{
	ImGui::Text("nowWeaponCnt : %d", weaponCnt);
	ImGui::Text("nowBuffCnt : %d", buffCnt);
	for (auto s : nowWeaponList)
	{
		if (s != nullptr)
			s->PostRender();
	}
	for (auto s : nowBuffList)
	{
		if (s != nullptr)
			s->PostRender();
	}
}

Skill* SkillManager::GetSkillByID(Skill::SKILL_ID id)
{
	for (auto s : skillTable)
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
		nowWeaponList.push_back(skillTable[(int)Skill::SKILL_ID::PISTOL_SHOT]);
		skillTable[(int)Skill::SKILL_ID::PISTOL_SHOT]->LevelUp();
		skillTable[(int)Skill::SKILL_ID::PISTOL_SHOT]->SetPlayer(player);
	}
		break; 
	case Player::PLAYER_ID::KIARA:
	{
		nowWeaponList.push_back(skillTable[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
		skillTable[(int)Skill::SKILL_ID::PHOENIX_SWORD]->LevelUp();
		skillTable[(int)Skill::SKILL_ID::PHOENIX_SWORD]->SetPlayer(player);
	}
			break;
	case Player::PLAYER_ID::BAELZ:
	{
		nowWeaponList.push_back(skillTable[(int)Skill::SKILL_ID::PLAY_DICE]);
		skillTable[(int)Skill::SKILL_ID::PLAY_DICE]->LevelUp();
		skillTable[(int)Skill::SKILL_ID::PLAY_DICE]->SetPlayer(player);
	}
		break;
	default:
		break;
	}
	for (auto s : skillTable)
		s->SetPlayer(player);

	Update_LevelUpAlbeList();
}

void SkillManager::Update_LevelUpAlbeList()
{
	// 2(stat), 3(extra)은 업데이트할 필요 없음
	levelUpAbleList[0].clear();
	levelUpAbleList[1].clear();
	totalWeightW = 0;
	totalWeightB = 0;

	switch (player->player_id)
	{
	case Player::PLAYER_ID::WATSON:
		if (skillTable[(int)Skill::SKILL_ID::PISTOL_SHOT]->GetLevelUpAble())
		{
			levelUpAbleList[0].push_back(skillTable[(int)Skill::SKILL_ID::PISTOL_SHOT]);
			totalWeightW += skillTable[(int)Skill::SKILL_ID::PISTOL_SHOT]->weight;
		}
		break;
	case Player::PLAYER_ID::KIARA:
		if (skillTable[(int)Skill::SKILL_ID::PHOENIX_SWORD]->GetLevelUpAble())
		{
			levelUpAbleList[0].push_back(skillTable[(int)Skill::SKILL_ID::PHOENIX_SWORD]);
			totalWeightW += skillTable[(int)Skill::SKILL_ID::PHOENIX_SWORD]->weight;
		}
		break;
	case Player::PLAYER_ID::BAELZ:
		if (skillTable[(int)Skill::SKILL_ID::PLAY_DICE]->GetLevelUpAble())
		{
			levelUpAbleList[0].push_back(skillTable[(int)Skill::SKILL_ID::PLAY_DICE]);
			totalWeightW += skillTable[(int)Skill::SKILL_ID::PLAY_DICE]->weight;
		}
		break;
	}

	if (weaponCnt == 6)
	{
		for (int i = 0; i < 6; i++)
		{
			if (nowWeaponList[i]->GetLevelUpAble())
			{
				levelUpAbleList[0].push_back(skillTable[(int)nowWeaponList[i]->id]);
				totalWeightW += skillTable[(int)nowWeaponList[i]->id]->weight;
			}
		}
	}
	else
	{
		int startIdx = (int)Skill::SKILL_ID::HOLO_BOMB;
		int endIdx= (int)Skill::SKILL_ID::SPIDER_COOKING;
		for (int i = startIdx; i <= endIdx; i++)
		{
			if (skillTable[i]->type == Skill::SKILL_TYPE::WEAPON)
			{
				if (skillTable[i]->GetLevelUpAble())
				{
					levelUpAbleList[0].push_back(skillTable[i]);
					totalWeightW += skillTable[i]->weight;
				}
			}
		}
	}

	if (buffCnt == 6)
	{
		for (int i = 0; i < 6; i++)
		{
			if (nowBuffList[i]->GetLevelUpAble())
			{
				levelUpAbleList[1].push_back(skillTable[(int)nowBuffList[i]->id]);
				totalWeightB += skillTable[(int)nowBuffList[i]->id]->weight;
			}
		}
	}
	else
	{
		int startIdx = (int)Skill::SKILL_ID::NURSE_HORN;
		int endIdx = (int)Skill::SKILL_ID::NINJA_HEADBAND;
		for (int i = startIdx; i <= endIdx; i++)
		{
			if (skillTable[i]->type == Skill::SKILL_TYPE::BUFFE)
			{
				if (skillTable[i]->GetLevelUpAble())
				{
					levelUpAbleList[1].push_back(skillTable[i]);
					totalWeightB += skillTable[i]->weight;
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
	if (levelUpAbleList[0].size() != 0)
	{
		int targetWeight = Random::Get()->GetRandomInt(1, totalWeightW);
		int nowWeight = 0;
		for (int i = 0; i < levelUpAbleList[0].size(); i++)
		{
			nowWeight += levelUpAbleList[0][i]->weight;
			if (nowWeight >= targetWeight)
			{
				return (int)levelUpAbleList[0][i]->id;
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
	if (levelUpAbleList[1].size() != 0)
	{
		int targetWeight = Random::Get()->GetRandomInt(1, totalWeightB);
		int nowWeight = 0;
		for (int i = 0; i < levelUpAbleList[1].size(); i++)
		{
			nowWeight += levelUpAbleList[1][i]->weight;
			if (nowWeight >= targetWeight)
			{
				return (int)levelUpAbleList[1][i]->id;
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
	int targetWeight = Random::Get()->GetRandomInt(1, totalWeightS);
	int nowWeight = 0;
	for (int i = 0; i < levelUpAbleList[2].size(); i++)
	{
		nowWeight += levelUpAbleList[2][i]->weight;
		if (nowWeight >= targetWeight)
		{
			return (int)levelUpAbleList[2][i]->id;
		}
	}
}

int SkillManager::GetLevelUpSkillID_E()
{
	int skill_idx = Random::Get()->GetRandomInt(0, levelUpAbleList[3].size() - 1);
	return (int)(levelUpAbleList[3][skill_idx]->id);
}

