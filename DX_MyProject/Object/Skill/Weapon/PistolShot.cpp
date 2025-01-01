#include "framework.h"

PistolShot::PistolShot()
	:Weapon(SKILL_ID::PISTOL_SHOT)
	, watson(nullptr)
	, revengeRate(0.15f)
	,revengeTime(2.0f),nowTime(0.0f)
{
	projDelay = 0.2f;
	nowProjDelay = 0.0f;
	projCnt = 0;

	weight = 3;
	skillName = "PISTOL SHOT";
	levelScripts.push_back("Shoots 3 Projectiles forward.");
	levelScripts.push_back("Shoot 2 additional shot, and each bullet can pierce +1 times.");
	levelScripts.push_back("Increase damage by 20%.");
	levelScripts.push_back("Bullets ricochet if hit limit is reached.");
	levelScripts.push_back("Each bullet can pierce +1 times. Reduce the time between attacks by 25%.");
	levelScripts.push_back("Increase damage by 20%.");
	levelScripts.push_back("For the next 2 seconds, 15% of all damage taken by target is stored in time. Then target takes total of stored damage.");

	skillDelayTable = { 0,1.33f, 1.33f, 1.33f, 1.33f, 1.0f,1.0f,1.0f };
	minDamageTable = { 0,8,8,10,10,10,12,12 };
	maxDamageTable = { 0,12,12,14,14,14,16,16 };
	projCntTalbe = { 0,3,5,5,5,5,5,5 };
	projSpd = 250.0f;
	hitLimitTable = { 0,1,2,2,2,3,3,3 };
	colliderIdxTable = { 0,0,0,0,0,0,0,0 };
	ricochetTable = { 0,0,0,0,1,1,1,1 };

	weaponType = WEAPON_TYPE::MULTI_SHOT;
	
	// 기본적으로 총알을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		Projectile* bullet = new WatsonBullet();
		bullet->SetOwner(this);
		projectiles.push_back(bullet);
	}
	enhanceDamage = 0.0f;
}

PistolShot::~PistolShot()
{
	watson = nullptr;
}

void PistolShot::Update()
{
	if (nowLevel == 0)return;

	if (watson == nullptr)
	{
		watson = dynamic_cast<Watson*>(player);
	}

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
			if (projCnt < projCntTalbe[nowLevel]+player->GetProjCnt()) // 투사체를 덜 발사함
			{
				WatsonBullet* proj = GetProjectTile<WatsonBullet>();
				
				float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
					* (1 + SkillManager::Get()->addMainWeaponDmgRate + SkillManager::Get()->damageRateShot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(damage, projSpd, hitLimitTable[nowLevel], 2.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(colliderIdxTable[nowLevel] + player->GetColIdxShot());
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				bool isRicochet = ricochetTable[nowLevel] > 0;
				proj->SetRicochet(isRicochet, ricochetTable[nowLevel]);
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

	UpdateBullet();

	// 반격
	if (nowLevel == 7)
	{
		if (nowTime < revengeTime)
			nowTime += DELTA;
		else
		{
			nowTime = 0.0f;
			const list<Enemy*>& revengeList = watson->GetRevnegeList();
			for (auto r : revengeList)
			{
				// if (r.first == nullptr)continue;

				if (r->is_active)
				{
					float rDamage = watson->GetRevengeDamage() * revengeRate;
					r->ChangeHP(rDamage, false);
				}
			}
			watson->ClearRevenge();
		}
	}
}

void PistolShot::Render()
{
	if (nowLevel == 0)return;

	for (auto p : projectiles)
	{
		p->Render();
	}
}

void PistolShot::PostRender()
{
	if (nowLevel == 0)return;

	ImGui::Text("watsonWeapon's skill level : %d", nowLevel);
	ImGui::Text("now enhance level : %d  now enhance rate : %f", enhanceLevel, enhanceRate);
	//for (Projectile *p : projectiles)
	//	p->PostRender();
}

bool PistolShot::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	else if (nowLevel == 7)
	{
		watson->SetRevenge(true);
	}
	return true;
}

bool PistolShot::LevelDown()
{
	if (nowLevel > 0)
	{
		nowLevel--;
		return true;
	}
	return false;
}

void PistolShot::UpdateBullet()
{
	for (auto p : projectiles)
		p->Update();
}

