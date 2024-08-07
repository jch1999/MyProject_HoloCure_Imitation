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

	weapon_type = WEAPON_TYPE::MULTI_SHOT;

	skillDelay_table = { 0,2.0f, 2.0f, 2.0f, 2.0f, 1.6f,1.6f,1.6f };
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
		nowCoolDown.push_back(0.0f);
		set<Enemy*> v;
		hitEnemies.push_back(v);
	}
	enhanceDamage = 0.0f;
}

BounceBall::~BounceBall()
{
	for (auto p : balls)
		delete p;
}

void BounceBall::UpdateBalls()
{
	for (int i = 0; i< projectiles.size();i++)
	{
		if (projectiles[i]->is_active)
		{
			projectiles[i]->Update();
			if (nowCoolDown[i] <= 0.0f)
			{
				// 충돌 검사
				pair<int, int> bPos = make_pair(projectiles[i]->pos.x / CELL_X, projectiles[i]->pos.y / CELL_Y);
				const list<Enemy*>& enemyList = EnemySpawner::Get()->GetPartition(bPos);
				for (auto e : enemyList)
				{
					float colDist = e->GetDamageCollider()->Size().GetLength() + projectiles[i]->GetCollider()->Size().x;
					if (colDist >= (projectiles[i]->pos - e->pos).GetLength())
					{
						if (projectiles[i]->GetCollider()->isCollision(e->GetDamageCollider()))
						{
							if (player->isCritical())
								e->ChangeHP(-(projectiles[i]->GetDamage() * 1.5f), true);
							else
								e->ChangeHP(-(projectiles[i]->GetDamage()), false);
							projectiles[i]->Hit();
							nowCoolDown[i] = hitCooldown;

							// 넉백 주기
							if (now_level >= 4)
							{
								Vector2 dir = (dynamic_cast<Ball*>(projectiles[i])->GetVelocity().Normalized());
								e->SetKnockBack(dir, 300.0f, 0.08f);
							}

							// 튕겨내기
							Vector2 vel = (dynamic_cast<Ball*>(projectiles[i]))->GetVelocity();
							Vector2 colPos = e->GetDamageCollider()->pos;
							Vector2 colSize = e->GetDamageCollider()->Size();
							if (projectiles[i]->pos.x < e->pos.x && vel.x > 0.0f)
								vel.x *= -1.0f;
							else if (projectiles[i]->pos.x > e->pos.x && vel.x < 0.0f)
								vel.x *= -1.0f;
							else if (vel.x == 0.0f)
								vel.x += e->GetMoveDir().x;
							
							if (projectiles[i]->pos.y < e->pos.y && vel.y>0.0f)
								vel.y *= -1.0f;
							else if (projectiles[i]->pos.y > e->pos.y && vel.y < 0.0f)
								vel.y *= -1.0f;
							(dynamic_cast<Ball*>(projectiles[i]))->SetVelocity(vel);

							// 충돌에서 벗어나게 밀어내기
							projectiles[i]->pos += (projectiles[i]->pos - e->GetDamageCollider()->pos).Normalized() * (colDist - (projectiles[i]->pos - e->pos).GetLength());
						}
					}
				}
			}
			else
				nowCoolDown[i] -= DELTA;
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
					Ball* proj = GetBall();
					float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
						* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
						+ player->GetATK()
						+ enhanceDamage;
					proj->SetStatus(damage, proj_spd, hitLimit_table[now_level], 3.0f);
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

Ball* BounceBall::GetBall()
{
	Ball* ball = nullptr;
	for (int i = 0; i < projectiles.size(); i++)// 비활성화 상태인 폭탄 하나를 찾아 사용
	{
		if (projectiles[i]->is_active == false)
		{
			ball = dynamic_cast<Ball*>(projectiles[i]);
			break;
		}
	}

	// 비활성 상태 폭탄 없음 == 폭탄이 부족함 -> 새로 생성
	if (ball == nullptr)
	{
		ball = new Ball();
		projectiles.push_back(ball);
	}
	ball->SetVelocity(Vector2(0, 0));
	return ball;
}
