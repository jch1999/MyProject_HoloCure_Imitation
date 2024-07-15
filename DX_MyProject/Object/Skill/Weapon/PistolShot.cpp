#include "framework.h"

PistolShot::PistolShot()
	:Weapon(SKILL_ID::PISTOL_SHOT)
{
	proj_delay = 0.2f;
	now_proj_delay = 0.0f;
	projCnt = 0;

	weight = 3;
	skill_name = "PISTOL SHOT";
	level_scripts.push_back("Shoots 3 Projectiles forward.");
	level_scripts.push_back("Shoot 2 additional shot, and each bullet can pierce +1 times.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Bullets ricochet if hit limit is reached.");
	level_scripts.push_back("Each bullet can pierce +1 times. Reduce the time between attacks by 25%.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("For the next 2 seconds, 15% of all damage taken by target is stored in time. Then target takes total of stored damage.(Not implemented)");

	skillDelay_table = { 0,1.33f, 1.33f, 1.33f, 1.33f, 1.0f,1.0f,1.0f };
	minDamage_table = { 0,8,8,10,10,10,12,12 };
	maxDamage_table = { 0,12,12,14,14,14,16,16 };
	projCnt_talbe = { 0,3,5,5,5,5,5,5 };
	hitLimit_table = { 0,1,2,2,2,3,3,3 };
	colliderIdx_table = { 0,0,0,0,0,0,0,0 };
	ricochet_table = { 0,0,0,0,1,1,1,1 };

	type = WEAPON_TYPE::MULTI_SHOT;
	
	// 기본적으로 총알을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		Projectile* bullet = new WatsonBullet(Vector2(20.0f, 16.0f));
		bullet->SetActive(false);
		bullet->GetCollider()->SetActive(false);

		projectiles.push_back(bullet);
		ricochetCnt.push_back(0);
		set<Enemy*> v;
		hitEnemies.push_back(v);
	}
	enhanceDamage = 0.0f;
}

PistolShot::~PistolShot()
{
	for (auto p : projectiles)
		delete p;
}

void PistolShot::Update()
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
			if (projCnt < projCnt_talbe[now_level]+player->GetProjCnt()) // 투사체를 덜 발사함
			{
				Projectile* proj = nullptr;
				for (int i = 0; i < projectiles.size();i++)// 비활성화 상태인 총알 하나를 찾아 사용
				{
					if (projectiles[i]->is_active == false)
					{
						proj = projectiles[i];
						ricochetCnt[i] = 0;
						hitEnemies[i].clear();
						break;
					}
				}

				// 비활성 상태 총알 없음 == 총알이 부족함 -> 새로 생성
				if (proj == nullptr)
				{
					proj = new WatsonBullet(Vector2(30.0f, 24.0f));
					projectiles.push_back(proj);
					ricochetCnt.push_back(0);
					set<Enemy*> v;
					hitEnemies.push_back(v);
				}

				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* (1 + SkillManager::Get()->add_MainWeapon_dmgRate + SkillManager::Get()->damageRate_Shot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(damage, 250.0f, hitLimit_table[now_level], 2.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxShot());
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

	// 충돌 처리
	for (int i=0;i< projectiles.size();i++)
	{
		Projectile* p = projectiles[i];
		if (!p->is_active)continue;

		p->Update();
		// 충돌 처리
		pair<int, int> pPos = make_pair((int)(p->pos.x) / CELL_X, (int)(p->pos.y) / CELL_Y);
		list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(pPos);
		for (auto e : enemyList)
		{
			if (!e->is_active)continue;
			
			if ((e->pos - p->pos).GetLength() < (p->GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength()) / 2.0f)
			{
				if (p->GetCollider()->isCollision(e->GetDamageCollider()))
				{
					// 이미 충돌한 적이 있다면 넘어가고
					if (hitEnemies[i].find(e)!=hitEnemies[i].end())continue;
					// 더 이상 부딪힐 횟수가 없다면 이 탄환의 충돌처리 종료
					if (!p->is_active)break;

					bool isCrt = player->isCritical();
					if (isCrt)
						e->ChangeHP(-(p->GetDamage()) * 1.5f, true);
					else
						e->ChangeHP(-(p->GetDamage()), false);
					p->Hit();
					hitEnemies[i].insert(e);

					if (ricochet_table[now_level] > 0 && !p->is_active) // 도탄 생성
					{
						int cnt = p->GetRemainHitCnt();
						int cnt2 = ricochetCnt[i];
						if (ricochetCnt[i] == 0)
						{
							int rand = Random::Get()->GetRandomInt(0, 4);
							switch (rand)
							{
							case 0:
							{
								Vector2 dir = Vector2(-1, -1) * p->move_dir;
								float newRot = atan(dir.y / dir.x) + 45;
								p->rot.z = newRot;
								p->SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							case 1:
							{
								Vector2 dir = Vector2(-1, -1) * p->move_dir;
								float newRot = atan(dir.y / dir.x) + 90;
								p->rot.z = newRot;
								p->SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							case 2:
							{
								Vector2 dir = Vector2(-1, -1) * p->move_dir;
								float newRot = atan(dir.y / dir.x) - 45;
								p->rot.z = newRot;
								p->SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							case 3:
							{
								Vector2 dir = Vector2(-1, -1) * p->move_dir;
								float newRot = atan(dir.y / dir.x) - 90;
								p->rot.z = newRot;
								p->SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							}
							float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
								* (1 + SkillManager::Get()->add_MainWeapon_dmgRate + SkillManager::Get()->damageRate_Shot)
								+ player->GetATK()
								+ enhanceDamage;
							p->SetStatus(damage, 250.0f, hitLimit_table[now_level], 2.0f);
							ricochetCnt[i]++;
							p->respwan();
							break;
						}
					}
				}
			}
		}
	}
}

void PistolShot::Render()
{
	if (now_level == 0)return;

	for (auto p : projectiles)
	{
		p->Render();
	}
}

void PistolShot::PostRender()
{
	if (now_level == 0)return;

	ImGui::Text("watsonWeapon's skill level : %d", now_level);
	ImGui::Text("now enhance level : %d  now enhance rate : %f", enhance_level, enhance_rate);
	//for (Projectile *p : projectiles)
	//	p->PostRender();
}

bool PistolShot::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool PistolShot::LevelDown()
{
	if (now_level > 0)
	{
		now_level--;
		return true;
	}
	return false;
}