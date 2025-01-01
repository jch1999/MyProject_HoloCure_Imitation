#include "framework.h"

EliteLavaBucket::EliteLavaBucket()
	:Weapon(Skill::SKILL_ID::ELITE_LAVA_BUCKET)
{
	weight = 3;
	skillName = "ELITE LAVA BUCKET";
	levelScripts.push_back("Drop lava on the ground, burning targets slowly.");
	levelScripts.push_back("Increase lava area by 20%.");
	levelScripts.push_back("Throw 2 lava buckets.");
	levelScripts.push_back("Increase damage by 30% and increase duration of lava by 1 second");
	levelScripts.push_back("Increase damage by 30%");
	levelScripts.push_back("Throw 3 lava buckets");
	levelScripts.push_back("Throw 4 lava buckets and increase lava size by 20%");

	skillDelayTable = { 0, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
	minDamageTable = { 0.0f, 6.0f, 6.0f, 6.0f, 10.0f, 14.0f, 14.0f, 14.0f };
	maxDamageTable = { 0.0f, 10.0f, 10.0f, 10.0f, 14.0f, 18.0f, 18.0f, 18.0f };
	colliderIdxTable = { 0, 1, 2, 2, 2, 2, 2, 3 };
	projLifetimeTable = { 0.0f, 3.0f, 3.0f, 3.0f, 4.5f, 4.5f, 4.5f, 4.5f };
	projCntTalbe = { 0, 1, 1, 2, 2, 2, 3, 4 };
	hitCooldown = 0.75f;
	projDelay = 0.08f;

	weaponType = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	for (int i = 0; i < 10; i++)
	{
		Projectile* bucket = new LavaBucket();
		projectiles.push_back(bucket);
		bucket->SetOwner(this);
	}
	enhanceDamage = 0.0f;
}

EliteLavaBucket::~EliteLavaBucket()
{
	for (auto p : buckets)
		delete p;
}

void EliteLavaBucket::Update()
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
				for (int i = 0; i < projCntTalbe[nowLevel]; i++)
				{
					SpawnBucket();
				}
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

	UpdateBuckets();
}

void EliteLavaBucket::Render()
{
	if (nowLevel == 0)return;

	for (auto p : buckets)
		p->Render();
}

void EliteLavaBucket::PostRender()
{
}

bool EliteLavaBucket::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool EliteLavaBucket::LevelDown()
{
	return false;
}

void EliteLavaBucket::UpdateBuckets()
{
	for (auto bucket : projectiles)
		bucket->Update();
}

void EliteLavaBucket::SpawnBucket()
{
	LavaBucket* proj = GetProjectTile<LavaBucket>();

	float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
		* (1 + SkillManager::Get()->addWeaponDmgRate + SkillManager::Get()->damageRateShot)
		+ player->GetATK()
		+ enhanceDamage;
	proj->SetStatus(damage, projSpd, hitLimitTable[nowLevel], projLifetimeTable[nowLevel], hitCooldown);
	float randomRot = Random::Get()->GetRandomFloat(0.0f, 360.0f);
	float dir = randomRot * M_PI / 180.0f;
	proj->rot.z = dir;
	if (randomRot >= 90.0f && randomRot <= 270.0f)
	{
		proj->SetDirection(Vector2(-cosf(dir), -sinf(dir)));
	}
	else
	{
		proj->SetDirection(Vector2(cosf(dir), sinf(dir)));
	}
	proj->SetColliderIdx(colliderIdxTable[nowLevel]);
	proj->pos = player->pos + player->GetAttackDir() * 50.0f;
	proj->respwan();
	projCnt++;
}
