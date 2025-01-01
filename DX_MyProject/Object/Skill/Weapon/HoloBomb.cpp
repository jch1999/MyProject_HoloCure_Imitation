#include "framework.h"

HoloBomb::HoloBomb()
	:Weapon(Skill::SKILL_ID::HOLO_BOMB)
{
	weight = 3;
	skillName = "HOLO BOMB";
	levelScripts.push_back("A bomb that explodes, dealing damage to all nearby targets.");
	levelScripts.push_back("Increase explosion size by 15%.");
	levelScripts.push_back("Increase damage by 20%.");
	levelScripts.push_back("Throw 2 bombs.");
	levelScripts.push_back("Reduce the time between attacks by 20%.");
	levelScripts.push_back("Increase explosion size by 20%.");
	levelScripts.push_back("Throw 3 bombs.");

	projDelay = 0.08f;

	weaponType = WEAPON_TYPE::MULTI_SHOT;

	skillDelayTable = { 0,2.0f, 2.0f, 2.0f, 2.0f, 1.6f,1.6f,1.6f };
	minDamageTable = { 0,15.0f,15.0f,15.0f,15.0f,15.0f,18.0f,18.0f };
	maxDamageTable = { 0,19.0f,19.0f,19.0f,19.0f,19.0f,22.0f,22.0f };
	projCntTalbe = { 0,1,1,1,2, 2,2,3 };
	projSpd = 7.0f;
	hitLimitTable = { 0,1,1,1,1,1,1,1 };
	// explosionCollider size table
	colliderIdxTable = { 0,0,1,1,1,1,2,2 };

	weaponType = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	// 기본적으로 폭탄과 폭발 효과를 10개 씩 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		Projectile* bomb = new Bomb();
		bomb->SetOwner(this);
		projectiles.push_back(bomb);
	}
	enhanceDamage = 0.0f;
}

HoloBomb::~HoloBomb()
{

}

void HoloBomb::Update()
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
				Bomb* proj = GetProjectTile<Bomb>();
				
				float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
					* (1 + SkillManager::Get()->addWeaponDmgRate + SkillManager::Get()->damageRateShot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(0.0f, projSpd, 1, -1.0f,0.0f);
				proj->SetExplosionStatus(damage * 1.5f, 0.0f, hitLimitTable[nowLevel], -1.0f, 0.0f);

				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(0);
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->SetTargetPos(proj->pos + player->GetAttackDir() * proj->GetTargetDist());
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

	UpdateBomb();
}

void HoloBomb::Render()
{
	if (nowLevel == 0)return;
	for (auto p : projectiles)
	{
		p->Render();
	}
}

void HoloBomb::PostRender()
{
}

bool HoloBomb::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool HoloBomb::LevelDown()
{
	return false;
}

void HoloBomb::UpdateBomb()
{
	for (auto b : projectiles)
	{
		b->Update();
	}
}
