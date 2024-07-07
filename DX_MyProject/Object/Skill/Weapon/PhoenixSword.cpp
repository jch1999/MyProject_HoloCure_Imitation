#include "framework.h"

PhoenixSword::PhoenixSword()
	:Weapon(Skill::SKILL_ID::PHOENIX_SWORD)
{
	weight = 3;
	skill_name = "PHOENIX SWORD";
	level_scripts.push_back("Short ranged slash in front.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Increase attack area by 25%.");
	level_scripts.push_back("Reduce the time between attacks by 15%.");
	level_scripts.push_back("Can hit twice per slash.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Sword is engulfed in flames, and can hit many times. Also leave a burning fire under hit targets.");
	
	minDamage_table = { 0,11.0f, 14.0f,14.0f, 14.0f, 14.0f, 17.0f,5.0f };
	maxDamage_table = { 0,15.0f, 18.0f,18.0f, 18.0f, 18.0f, 21.0f,9.0f };
	colliderIdx_table = { 0,0,0,1,1,1,1,1 };
	hitCooldown_table = { 0,0.33f,0.33f,0.33f,0.33f,0.08f,0.08f,0.07f };
	hiLimit_table = { 0,1,1,1,1,2,2,2 };
	skillDelay_table = { 0, 1.17f, 1.17f, 1.17f, 1.0f, 1.0f, 1.0f, 1.0f };
	blaze_hitCool = 1.0f;

	slash = new KiaraSlash();
	for (int i = 0; i < 10; i++)
	{
		blazes.push_back(new Blaze());
	}

	now_skill_delay = 0.0f;
	playTime_table.push_back(1.0f);
	play_time = 0.0f;
	enhanceDamage = 0.0f;
}

PhoenixSword::~PhoenixSword()
{
	delete slash;
	for (auto b : blazes)
		delete b;
}

void PhoenixSword::Update()
{
	if (now_level == 0)return;
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		now_skill_delay += DELTA;

		if (now_skill_delay >= skillDelay_table[now_level])
		{
			now_skill_delay = 0.0f;
			action_status = Skill::SKILL_STATUS::PLAY;

			// slash 정보 초기화
			float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
				* (1 + SkillManager::Get()->add_MainWeapon_dmgRate + SkillManager::Get()->damageRate_Melee)
				+ player->GetATK()
				+ enhanceDamage;
			slash->SetStatus(damage, 250.0f, -1, playTime_table[0]);
			slash->SetDirection(player->GetAttackDir());
			slash->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
			slash->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxMelee());
			slash->SetClipIdx(((now_level == max_level) ? 1 : 0));
			slash->respwan();
		}
	}
		break;
	case Skill::SKILL_STATUS::PLAY:
	{
		play_time += DELTA;

		if (slash->GetCollider()->is_active&&play_time>=0.5f)
		{
			slash->GetCollider()->SetActive(false); 
		}

		if (play_time > playTime_table[0])
		{
			play_time = 0.0f;
			enemyCooltimes_s.clear();
			enemyHitCount.clear();
			enemyNowFrame_s.clear();
			removeList_s.clear();
			action_status = Skill::SKILL_STATUS::COOLDOWN;
			slash->is_active = false;
			return;
		}
		else
		{
			UpdateSlash();
		}
	}
		break;
	default:
		break;
	}

	UpdateBlaze();
}

void PhoenixSword::Render()
{
	if (now_level == 0)return;

	slash->Render();
	for (auto b : blazes)
		b->Render();
}

void PhoenixSword::PostRender()
{
	if (now_level == 0)return;

	ImGui::Text("PhoenixBlade's skill level : %d", now_level);
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
	slash->PostRender();
	
	for (auto b : blazes)
		b->PostRender();
}

bool PhoenixSword::LevelUp()
{
	if (now_level == max_level)return false;
	
	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
	
}

void PhoenixSword::UpdateSlash()
{
	slash->pos = player->pos + slash->move_dir * 60.0f;
	slash->Update();

	// 충돌 중인 Enemey 검출
	enemyNowFrame_s.clear();
	removeList_s.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash의 pos의 CELL 위치를 중앙으로 3x3 영역을 검사
	pair<int, int> sPos = make_pair(slash->pos.x / CELL_X, slash->pos.y / CELL_Y);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first + i, sPos.second + j));
			for (auto e : enemyList)
			{
				if (!e->is_active)continue;
				if (slash->GetCollider()->isCollision(e->GetDamageCollider()))
					enemyNowFrame_s.push_back(e);
			}
		}
	}
	
	// 리스트 갱신
	for (auto e : enemyNowFrame_s)
	{
		auto found = enemyCooltimes_s.find(e);
		// 기존에 존재하지 않음 - 추가 및 바로 공격하게 설정
		if (found == enemyCooltimes_s.end())
		{
			enemyCooltimes_s[e] = 0.0f;
			enemyHitCount[e] = 0;
		}
		// 기존에 존재 - 시간 감소
		else
		{
			enemyCooltimes_s[e] = found->second - DELTA;
		}
	}

	// 시간 경과 체크, coolTime이 지났으면 damage주기
	for (auto m : enemyCooltimes_s)
	{
		//m.second -= DELTA;
		if (m.second <= 0.0f)
		{
			if (enemyHitCount[m.first] < hiLimit_table[now_level])
			{
				enemyCooltimes_s[m.first] = hitCooldown_table[now_level];
				if (player->isCritical())
				{
					m.first->ChangeHP(-(slash->GetDamage()) * 1.5f, true);
				}
				else
				{
					m.first->ChangeHP(-(slash->GetDamage()), false);
				}
				enemyHitCount[m.first]++;

				// 각성 상태 + 25% 확률이면
				// enemy를 따라다니며 지속데미지를 주는 불 생성
				if (now_level == max_level)
				{
					int rand = Random::Get()->GetRandomInt(0, 4);
					if (rand == 0)
					{
						// enemy 위치에 blaze 생성
						Projectile* blaze = nullptr;
						for (auto b : blazes)
						{
							if (!b->is_active)
							{
								blaze = b;
								break;
							}
						}
						if (blaze == nullptr)
						{
							blaze = new Blaze();
							blazes.push_back(blaze);
						}
						blaze->pos = m.first->pos;
						float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
							+ player->GetATK()
							+ enhanceDamage;
						blaze->SetStatus(damage * 0.2f, 0.0f, -1, 5.0f);
						blaze->respwan();
					}
				}
			}
			// 이미 죽은 Enemy를 제거 리스트에 추가
			if (!m.first->is_active)
			{
				removeList_s.push_back(m.first);
			}

			
		}
	}

	// 제거
	for (auto e : removeList_s)
	{
		enemyCooltimes_s.erase(enemyCooltimes_s.find(e));
	}
}

void PhoenixSword::UpdateBlaze()
{
	for (auto b : blazes)
	{
		if (!b->is_active)continue;
		b->Update();
		if (!b->is_active) // 시간이 지나 비활성화
		{
			enemyCooltimes_b.clear();
			enemyNowFrame_b.clear();
			removeList_b.clear();
			continue;
		}
		enemyNowFrame_b.clear();
		removeList_b.clear();

		const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
		for (auto e : enemyList)
		{
			if (!e->is_active)continue;
			if (b->GetCollider()->isCollision(e->GetDamageCollider()))
				enemyNowFrame_b.push_back(e);
		}

		// 기존에 존재하지 않으면 추가, 존재하면 시간 경과
		for (auto e : enemyNowFrame_b)
		{
			auto found = enemyCooltimes_b.find(e);
			if (found == enemyCooltimes_b.end())
			{
				enemyCooltimes_b[e] = 0.0f;
			}
			else
			{
				enemyCooltimes_b[found->first] = found->second - DELTA;
			}
		}

		// 시간 경과 체크, coolTime이 지났으면 damage주기
		for (auto m : enemyCooltimes_b)
		{
			
			//m.second -= DELTA;
			if (m.second <= 0.0f)
			{
				enemyCooltimes_b[m.first] = blaze_hitCool;
				// blaze.. 크리티컬 적용 o x? 일단 x로
				m.first->ChangeHP(-(b->GetDamage()), false);
				
				if (!m.first->is_active)
				{
					removeList_b.push_back(m.first);
				}
			}
		}

		// 제거
		for (auto e : removeList_b)
		{
			enemyCooltimes_b.erase(enemyCooltimes_b.find(e));
		}
	}
}

bool PhoenixSword::LevelDown()
{
	if (now_level > 0)
	{
		now_level--;
		return true;
	}
	return false;
}