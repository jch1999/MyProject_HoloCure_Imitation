#include "framework.h"

PhoenixSword::PhoenixSword()
	:Weapon(Skill::SKILL_ID::PHOENIX_SWORD)
{
	weight = 3;
	skillName = "PHOENIX SWORD";
	levelScripts.push_back("Short ranged projectiles in front.");
	levelScripts.push_back("Increase damage by 20%.");
	levelScripts.push_back("Increase attack area by 25%.");
	levelScripts.push_back("Reduce the time between attacks by 15%.");
	levelScripts.push_back("Can hit twice per projectiles.");
	levelScripts.push_back("Increase damage by 20%.");
	levelScripts.push_back("Sword is engulfed in flames, and can hit many times. Also leave a burning fire under hit targets.");
	
	weaponType = WEAPON_TYPE::MELEE;

	minDamageTable = { 0,11.0f, 14.0f,14.0f, 14.0f, 14.0f, 17.0f,5.0f };
	maxDamageTable = { 0,15.0f, 18.0f,18.0f, 18.0f, 18.0f, 21.0f,9.0f };
	colliderIdxTable = { 0,0,0,1,1,1,1,1 };
	hitCooldownTable = { 0,0.33f,0.33f,0.33f,0.33f,0.08f,0.08f,0.07f };
	hitLimitTable = { 0,1,1,1,1,2,2,2 };
	skillDelayTable = { 0, 1.17f, 1.17f, 1.17f, 1.0f, 1.0f, 1.0f, 1.0f };
	blazeHitCool = 1.0f;

	// Create KiaraSlash
	projectiles.emplace_back(new KiaraSlash());
	projectiles[0]->SetOwner(this);

	for (int i = 0; i < 10; i++)
	{
		projectiles.push_back(new Blaze());
		projectiles[i]->SetOwner(this);
	}

	nowSkillDelay = 0.0f;
	playTimeTable.push_back(1.0f);
	playTime = 0.0f;
	enhanceDamage = 0.0f;
}

PhoenixSword::~PhoenixSword()
{
	/*for (auto b : projectiles)
		delete b;*/
}

void PhoenixSword::Update()
{
	if (nowLevel == 0)return;
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		nowSkillDelay += DELTA;

		if (nowSkillDelay >= skillDelayTable[nowLevel])
		{
			nowSkillDelay = 0.0f;
			action_status = Skill::SKILL_STATUS::PLAY;

			// projectiles[0] 정보 초기화
			float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], maxDamageTable[nowLevel] + 1)
				* (1 + SkillManager::Get()->addMainWeaponDmgRate + SkillManager::Get()->damageRateMelee)
				+ player->GetATK()
				+ enhanceDamage;
			projectiles[0]->SetStatus(damage, 250.0f, -1, playTimeTable[0]);
			projectiles[0]->SetDirection(player->GetAttackDir());
			projectiles[0]->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
			projectiles[0]->SetColliderIdx(colliderIdxTable[nowLevel] + player->GetColIdxMelee());
			projectiles[0]->SetClipIdx(((nowLevel == maxLevel) ? 1 : 0));
			projectiles[0]->respwan();
		}
	}
		break;
	case Skill::SKILL_STATUS::PLAY:
	{
		playTime += DELTA;

		if (projectiles[0]->GetCollider()->is_active&&playTime>=0.5f)
		{
			projectiles[0]->GetCollider()->SetActive(false); 
		}

		if (playTime > playTimeTable[0])
		{
			playTime = 0.0f;
			action_status = Skill::SKILL_STATUS::COOLDOWN;
			projectiles[0]->is_active = false;
			return;
		}
		else
		{
			projectiles[0]->pos = player->pos + projectiles[0]->moveDir * 60.0f;
		}
	}
		break;
	default:
		break;
	}

	for (auto& proj : projectiles)
	{
		proj->Update();
	}
}

void PhoenixSword::Render()
{
	if (nowLevel == 0)return;

	projectiles[0]->Render();
	for (auto b : projectiles)
		b->Render();
}

void PhoenixSword::PostRender()
{
	if (nowLevel == 0)return;

	ImGui::Text("PhoenixBlade's skill level : %d", nowLevel);
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
		ImGui::Text("now status : cooldown");
		break;
	case Skill::SKILL_STATUS::PLAY:
		ImGui::Text("now status : play");
		break;
	default:
		break;
	}
	projectiles[0]->PostRender();
	
	for (auto b : projectiles)
		b->PostRender();
}

bool PhoenixSword::LevelUp()
{
	if (nowLevel == maxLevel)return false;
	
	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	else if (nowLevel == 7)
	{
		KiaraSlash* slash = dynamic_cast<KiaraSlash*>(projectiles[0]);
		if (slash)
		{
			slash->ActiveAwaken();
		}
	}
	projectiles[0]->SetHitLimit(hitLimitTable[nowLevel]);
	projectiles[0]->SetCoolDown(hitCooldownTable[nowLevel]);
	return true;
	
}

Blaze* PhoenixSword::GetBlaze()
{
	Blaze* blaze = GetProjectTile<Blaze>();
	
	float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], maxDamageTable[nowLevel] + 1)
		+ player->GetATK()
		+ enhanceDamage;
	blaze->SetStatus(damage * 0.2f, 0.0f, -1, 5.0f);

	return blaze;
}

bool PhoenixSword::LevelDown()
{
	if (nowLevel > 0)
	{
		nowLevel--;
		return true;
	}
	return false;
}