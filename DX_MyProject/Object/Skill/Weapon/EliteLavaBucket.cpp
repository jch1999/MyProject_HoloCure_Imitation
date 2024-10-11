#include "framework.h"

EliteLavaBucket::EliteLavaBucket()
	:Weapon(Skill::SKILL_ID::ELITE_LAVA_BUCKET)
{
	weight = 3;
	skill_name = "ELITE LAVA BUCKET";
	level_scripts.push_back("Drop lava on the ground, burning targets slowly.");
	level_scripts.push_back("Increase lava area by 20%.");
	level_scripts.push_back("Throw 2 lava buckets.");
	level_scripts.push_back("Increase damage by 30% and increase duration of lava by 1 second");
	level_scripts.push_back("Increase damage by 30%");
	level_scripts.push_back("Throw 3 lava buckets");
	level_scripts.push_back("Throw 4 lava buckets and increase lava size by 20%");

	skillDelay_table = { 0, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
	minDamage_table = { 0.0f, 6.0f, 6.0f, 6.0f, 10.0f, 14.0f, 14.0f, 14.0f };
	maxDamage_table = { 0.0f, 10.0f, 10.0f, 10.0f, 14.0f, 18.0f, 18.0f, 18.0f };
	colliderIdx_table = { 0, 1, 2, 2, 2, 2, 2, 3 };
	projLifetime_table = { 0.0f, 3.0f, 3.0f, 3.0f, 4.5f, 4.5f, 4.5f, 4.5f };
	hitCooldown = 0.75f;
	proj_delay = 0.08f;

	weapon_type = WEAPON_TYPE::MULTI_SHOT;
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
	if (now_level == 0)return;
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		now_skill_delay += DELTA;
		if (now_skill_delay >= skillDelay_table[now_level])
		{
			action_status = SKILL_STATUS::PLAY;
			now_skill_delay = 0.0f;
		}
	}
	break;
	case Skill::SKILL_STATUS::PLAY:
	{
		if (now_proj_delay < proj_delay)
		{
			now_proj_delay += DELTA;
		}
		else
		{
			now_proj_delay = 0.0f;
			if (projCnt < projCnt_talbe[now_level] + player->GetProjCnt()) // 투사체를 덜 발사함
			{
				for (int i = 0; i < projCnt_talbe[now_level]; i++)
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
	if (now_level == 0)return;

	for (auto p : buckets)
		p->Render();
}

void EliteLavaBucket::PostRender()
{
}

bool EliteLavaBucket::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
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

	float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
		* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
		+ player->GetATK()
		+ enhanceDamage;
	proj->SetStatus(damage, proj_spd, hitLimit_table[now_level], projLifetime_table[now_level], hitCooldown);
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
	proj->SetColliderIdx(colliderIdx_table[now_level]);
	proj->pos = player->pos + player->GetAttackDir() * 50.0f;
	proj->respwan();
	projCnt++;
}
