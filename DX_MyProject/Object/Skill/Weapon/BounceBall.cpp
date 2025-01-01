#include "framework.h"

BounceBall::BounceBall()
	:Weapon(SKILL_ID::BOUNCE_BALL)
{
	weight = 4;
	skillName = "BOUNCE BALL";
	levelScripts.push_back("Drops a falling bounce ball on a random target.");
	levelScripts.push_back("Increase damage by 20%.");
	levelScripts.push_back("Drop 2 balls.");
	levelScripts.push_back("Gain knockback effect.");
	levelScripts.push_back("Drop 3 balls.");
	levelScripts.push_back("Reduce the time between attacks by 15%.");
	levelScripts.push_back("Increase damage by 30% and drop 4 balls.");

	projDelay = 0.08f;

	skillDelayTable = { 0,2.0f, 2.0f, 2.0f, 2.0f, 2.0f,1.7f,1.7f };
	minDamageTable = { 0,12.0f,14.0f,14.0f,14.0f,14.0f,14.0f,18.0f };
	maxDamageTable = { 0,16.0f,18.0f,18.0f,18.0f,18.0f,18.0f,22.0f };
	projCntTalbe = { 0,1,1,2,2,3,3,4 };
	projSpd = 8.0f;
	hitLimitTable = { 0,1,1,1,1,1,1,1 };
	hitCooldown = 0.5f;

	weaponType = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	// 기본적으로 폭탄과 폭발 효과를 10개 씩 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		Projectile* ball = new Ball();
		ball->SetOwner(this);
		projectiles.push_back(ball);
	}
	enhanceDamage = 0.0f;
}

BounceBall::~BounceBall()
{
	
}

void BounceBall::UpdateBalls()
{
	for (int i = 0; i< projectiles.size();i++)
	{
		if (projectiles[i]->is_active)
		{
			projectiles[i]->Update();
		}
	}
}

bool BounceBall::LevelDown()
{
	return false;
}

void BounceBall::Update()
{
	if (nowLevel < 1)return;

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
					Ball* proj = GetProjectTile<Ball>();
					float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
						* (1 + SkillManager::Get()->addWeaponDmgRate + SkillManager::Get()->damageRateShot)
						+ player->GetATK()
						+ enhanceDamage;
					proj->SetStatus(damage, projSpd, hitLimitTable[nowLevel], 3.0f);
					proj->SetCoolDown(0.5f);
					if (nowLevel >= 4)
						proj->SetKnockBack(true);

					proj->SetColliderIdx(0);
					const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetActiveEnemies();
					int targetEnemyIdx = Random::Get()->GetRandomInt(0, enemyList.size()-1);
					proj->pos = Vector2(enemyList[targetEnemyIdx]->pos + Vector2(0.0f, 150.0f));
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

	UpdateBalls();
}

void BounceBall::Render()
{
	if (nowLevel < 1) return;

	for (auto b : projectiles)
		b->Render();
}

void BounceBall::PostRender()
{
}

bool BounceBall::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}
