#include "framework.h"

CEOTear::CEOTear()
	:Weapon(SKILL_ID::CEO_TEAR)
{
	weight = 2;
	skillName = "CEO'S TEAR";
	levelScripts.push_back("Fires rapid tears at random targets.");
	levelScripts.push_back("Increases damage by 20%.");
	levelScripts.push_back("Shoot 2 tears.");
	levelScripts.push_back("Reduce the time between attacks by 33%.");
	levelScripts.push_back("Tears are 25% faster and increase damage by 20%.");
	levelScripts.push_back("Reduce the time between attacks by 50%.");
	levelScripts.push_back("Shoot 4 tears.");
	
	skillDelayTable = { 0.0f,0.5f,0.5f,0.5f,0.33f,0.33f,0.17f,0.17f };
	minDamageTable = { 0.0f,8.0f,10.0f,10.0f,10.0f,12.0f,12.0f,12.0f };
	maxDamageTable = { 0.0f,12.0f,14.0f,14.0f,14.0f,16.0f,16.0f,16.0f };
	projCntTalbe = { 0,1,1,2,2,2,2,4 };
	projDelay = 0.15f;
	projSpdTable = { 0.0f,200.0f,200.0f,200.0f,200.0f,250.0f,250.0f,250.0f };
	hitLimitTable = { 0,1,1,1,1,1,1,1 };

	weaponType = WEAPON_TYPE::MULTI_SHOT;

	// 기본적으로 눈물을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 8; i++)
	{
		Projectile* tear = new Tear();
		tear->SetActive(false);
		tear->GetCollider()->SetActive(false);
		tear->SetOwner(this);

		projectiles.push_back(tear);
	}
	enhanceDamage = 0.0f;
}

CEOTear::~CEOTear()
{
	for (auto proj : projectiles)
	{
		delete proj;
	}
	projectiles.clear();
}

void CEOTear::UpdateTears()
{
	for (auto proj : projectiles)
	{
		if (proj->is_active)
		{
			proj->Update();
		}
	}
}

bool CEOTear::LevelDown()
{
	return false;
}

void CEOTear::Update()
{
	if (nowLevel == 0)return;

	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		nowSkillDelay += DELTA;
		if (nowSkillDelay >= skillDelayTable[nowLevel])
		{
			action_status = SKILL_STATUS::PLAY;
			nowSkillDelay = 0.0f;
		}
	}
		break;
	case Skill::SKILL_STATUS::PLAY:
	{
		if (nowProjDelay < projDelay)
		{
			nowProjDelay += DELTA;
		}
		else
		{
			nowProjDelay = 0.0f;
			if (projCnt < projCntTalbe[nowLevel] + player->GetProjCnt()) // 투사체를 덜 발사함
			{
				Tear* proj = GetProjectTile<Tear>();

				float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
					* (1 + SkillManager::Get()->addWeaponDmgRate + SkillManager::Get()->damageRateShot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(damage, projSpdTable[nowLevel], hitLimitTable[nowLevel], 5.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(0);
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				proj->respwan();

				projCnt++;
			}
			else // 투사체 발사가 끝났으니 스킬은 재사용 대기 상태로
			{
				projCnt = 0;
				action_status = SKILL_STATUS::COOLDOWN;
			}
		}
	}
		break;
	default:
		break;
	}
	UpdateTears();
}

void CEOTear::Render()
{
	if (nowLevel == 0)return;
	for (auto proj : projectiles)
	{
		proj->Render();
	}
}

void CEOTear::PostRender()
{
}

bool CEOTear::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}
