#include "framework.h"

PlayDice::PlayDice()
	:Weapon(SKILL_ID::PLAY_DICE)
	, proj_delay(0.2f), now_proj_delay(0.0f)
	, projCnt(0)
{
	skillDelay_table = { 0, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f };
	minDamage_table = { 0,2,3,3,3,3,4,8 };
	maxDamage_table = { 0,6,7,7,7,7,4,8 };
	projCnt_talbe = { 0, 1, 1, 2, 2, 2, 2, 3 };
	projSPD_table = { 0,16,16,16,19,19,19,19 };
	hitLimt_table = { 0, 4, 4, 4, 4, 4, 4, 4 };	// 첫 충돌 1, 도탄 3
	colliderIdx_table = { 0,0,0,0,2,2,2,2 };
	ricochet_table = { 0,3,3,3,3,3,3,3 };
	knockbackSpeed_table = { 0,0,0,0,0,5,5,5 };
	targetDist_table = { 0,200.0f,200.0f,200.0f,250.0f,250.0f,250.0f,250.0f };

	type = WEAPON_TYPE::MULTI_SHOT;

	// 기본적으로 총알을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		projectiles.push_back(new BaelzDice(Vector2(36.0f, 36.0f)));
		ricochetCnt.push_back(0);
		vector<Enemy*> v;
		hitEnemies.push_back(v);
	}
	enhanceDamage = 0.0f;
}

PlayDice::~PlayDice()
{
	for (auto p : projectiles)
		delete p;
}

void PlayDice::Update()
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
				Projectile* proj = GetTargetProj();
				int diceEye = GetDiceEye();
				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* diceEye // 주사위 눈 만큼을 기본 데미지에 곱한다
					+ player->GetATK((UINT)Weapon::WEAPON_TYPE::MULTI_SHOT)
					+ enhanceDamage;
				proj->SetStatus(damage, 100.0f * projSPD_table[now_level], hitLimt_table[now_level], 10.0f);
				proj->SetDirection(player->GetAttackDir());
				int clip_idx = max_level == now_level ? 6 + diceEye-1 : diceEye-1;
				proj->SetClipIdx(clip_idx);
				proj->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxShot());
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				proj->SetTargetDist(targetDist_table[now_level]);
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
	const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	for (int i = 0; i < projectiles.size(); i++)
	{
		Projectile* p = projectiles[i];
		if (!p->is_active)continue;

		p->Update();
		// 충돌 처리
		for (auto e : enemyList)
		{
			if (!e->is_active)continue;

			if (p->GetCollider()->isCollision(e->GetDamageCollider()))
			{
				bool exist = false;
				for (auto e2 : hitEnemies[i])
				{
					if (e == e2)
					{
						exist = true;
						break;
					}
				}
				// 이미 충돌한 적이 있다면 넘어가고
				if (exist)continue;
				// 더 이상 부딪힐 횟수가 없다면 이 탄환의 충돌처리 종료
				if (!p->is_active)break;

				e->ChangeHP(-(p->GetDamage()));
				p->Hit();
				hitEnemies[i].push_back(e);

				if (ricochet_table[now_level] > 0) // 도탄 생성
				{
					int cnt = p->GetRemainHitCnt();
					int cnt2 = ricochetCnt[i];
					if (ricochetCnt[i] < ricochet_table[now_level])
					{
						float newRot = Random::Get()->GetRandomFloat(0, 360.0f);
						p->SetDirection(Vector2(cosf(newRot), sinf(newRot)));
						p->rot.z = newRot;
						ricochetCnt[i]++;
						p->respwan();
						break;
					}
				}
			}
		}
	}
}

void PlayDice::Render()
{
	if (now_level == 0)return;

	for (auto p : projectiles)
	{
		p->Render();
	}
}

void PlayDice::PostRender()
{
	if (now_level == 0)return;

	ImGui::Text("BaelzDice's skill level : %d", now_level);
	switch (action_status)
	{
	case SKILL_STATUS::COOLDOWN:
		ImGui::Text("Status : Cooldown");
		break;
	case SKILL_STATUS::PLAY:
		ImGui::Text("Status : Play");
		break;
	default:
		break;
	}
}

bool PlayDice::LevelUp()
{
	if (now_level != max_level)
	{
		now_level++;
		return true;
	}
	else
	{
		enhanceDamage += 2.0f;
	}
	return false;
}

bool PlayDice::LevelDown()
{
	if (now_level > 0)
	{
		now_level--;
		return true;
	}
	return false;
}

int PlayDice::GetDiceEye()
{
	int rand = Random::Get()->GetRandomInt(0, 100);

	if (rand >= 95)
		return 6;
	else if (rand >= 80)
		return 5;
	else if (rand >= 65)
		return 4;
	else if (rand >= 50)
		return 3;
	else if (rand >= 25)
		return 2;
	else
		return 1;
}

Projectile* PlayDice::GetTargetProj()
{
	Projectile* proj = nullptr;
	for (int i = 0; i < projectiles.size(); i++)// 비활성화 상태인 주사위 하나를 찾아 사용
	{
		if (projectiles[i]->is_active == false)
		{
			proj = projectiles[i];
			ricochetCnt[i] = 0;
			hitEnemies[i].clear();
			break;
		}
	}

	// 비활성 상태 주사위 없음 -> 새로 생성
	if (proj == nullptr)
	{
		proj = new BaelzDice(Vector2(36.0f, 36.0f));
		projectiles.push_back(proj);
		ricochetCnt.push_back(0);
		vector<Enemy*> v;
		hitEnemies.push_back(v);
	}
	return proj;
}
