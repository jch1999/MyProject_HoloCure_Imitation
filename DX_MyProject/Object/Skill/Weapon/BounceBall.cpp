#include "framework.h"

BounceBall::BounceBall()
	:Weapon(SKILL_ID::BOUNCE_BALL)
{
	weight = 4;
	skill_name = "BOUNCE BALL";
	level_scripts.push_back("Drops a falling bounce ball on a random target.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Drop 2 balls.");
	level_scripts.push_back("Gain knockback effect.");
	level_scripts.push_back("Drop 3 balls.");
	level_scripts.push_back("Reduce the time between attacks by 15%.");
	level_scripts.push_back("Increase damage by 30% and drop 4 balls.");

	proj_delay = 0.08f;

	skillDelay_table = { 0,2.0f, 2.0f, 2.0f, 2.0f, 2.0f,1.7f,1.7f };
	minDamage_table = { 0,12.0f,14.0f,14.0f,14.0f,14.0f,14.0f,18.0f };
	maxDamage_table = { 0,16.0f,18.0f,18.0f,18.0f,18.0f,18.0f,22.0f };
	projCnt_talbe = { 0,1,1,2,2,3,3,4 };
	proj_spd = 8.0f;
	hitLimit_table = { 0,1,1,1,1,1,1,1 };
	hitCooldown = 0.5f;

	weapon_type = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	// 기본적으로 폭탄과 폭발 효과를 10개 씩 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		Projectile* ball = new Ball();
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
	if (now_level < 1)return;

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
					Ball* proj = GetProjectTile<Ball>();
					float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
						* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
						+ player->GetATK()
						+ enhanceDamage;
					proj->SetStatus(damage, proj_spd, hitLimit_table[now_level], 3.0f);
					proj->SetCoolDown(0.5f);
					if (now_level >= 4)
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
	if (now_level < 1) return;

	for (auto b : projectiles)
		b->Render();
}

void BounceBall::PostRender()
{
}

bool BounceBall::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}
