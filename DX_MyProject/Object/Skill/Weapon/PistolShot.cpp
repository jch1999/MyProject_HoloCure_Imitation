#include "framework.h"

PistolShot::PistolShot()
	:Weapon(SKILL_ID::PISTOL_SHOT)
	,proj_delay(0.2f),now_proj_delay(0.0f)
	,projCnt(0)
{
	skillDelay_table = { 0,1.33f, 1.33f, 1.33f, 1.33f, 1.0f,1.0f,1.0f };
	minDamage_table = { 0,8,8,10,10,10,12,12 };
	maxDamage_table = { 0,12,12,14,14,14,16,16 };
	projCnt_talbe = { 0,3,5,5,5,5,5,5 };
	hitLimt_table = { 0,1,2,2,2,3,3,3 };
	colliderIdx_table = { 0,0,0,0,0,0,0,0 };
	ricochet_table = { 0,0,0,0,1,1,1,1 };

	type = WEAPON_TYPE::MULTI_SHOT;
	
	// �⺻������ �Ѿ��� 10�� �������� ���� ��Ȱ��
	for (int i = 0; i < 10; i++)
	{
		Projectile* bullet = new WatsonBullet(Vector2(20.0f, 16.0f));
		bullet->SetActive(false);
		bullet->GetCollider()->SetActive(false);

		projectiles.push_back(bullet);
		ricochetCnt.push_back(0);
		vector<Enemy*> v;
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
			if (projCnt < projCnt_talbe[now_level]+player->GetProjCnt()) // ����ü�� �� �߻���
			{
				Projectile* proj = nullptr;
				for (int i = 0; i < projectiles.size();i++)// ��Ȱ��ȭ ������ �Ѿ� �ϳ��� ã�� ���
				{
					if (projectiles[i]->is_active == false)
					{
						proj = projectiles[i];
						ricochetCnt[i] = 0;
						hitEnemies[i].clear();
						break;
					}
				}

				// ��Ȱ�� ���� �Ѿ� ���� == �Ѿ��� ������ -> ���� ����
				if (proj == nullptr)
				{
					proj = new WatsonBullet(Vector2(30.0f, 24.0f));
					projectiles.push_back(proj);
					ricochetCnt.push_back(0);
					vector<Enemy*> v;
					hitEnemies.push_back(v);
				}

				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					+ player->GetATK((UINT)Weapon::WEAPON_TYPE::MULTI_SHOT)
					+ enhanceDamage;
				proj->SetStatus(damage, 250.0f, hitLimt_table[now_level], 2.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxShot());
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				proj->respwan();
				
				projCnt++;
			}
			else // ����ü �߻簡 �������� ��ų�� ���� ��� ���·�
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

	// �浹 ó��
	const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	for (int i=0;i< projectiles.size();i++)
	{
		Projectile* p = projectiles[i];
		if (!p->is_active)continue;

		p->Update();
		// �浹 ó��
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
				// �̹� �浹�� ���� �ִٸ� �Ѿ��
				if (exist)continue;
				// �� �̻� �ε��� Ƚ���� ���ٸ� �� źȯ�� �浹ó�� ����
				if (!p->is_active)break;

				e->GetDamage(p->GetDamage());
				p->Hit();
				hitEnemies[i].push_back(e);

				if (ricochet_table[now_level] > 0 &&!p->is_active) // ��ź ����
				{
					int cnt = p->GetRemainHitCnt();
					int cnt2=ricochetCnt[i];
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
							+ player->GetATK((UINT)Weapon::WEAPON_TYPE::MULTI_SHOT)
							+ enhanceDamage;
						p->SetStatus(damage, 250.0f, hitLimt_table[now_level], 2.0f);
						ricochetCnt[i]++;
						p->respwan();
						break;
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

	//for (Projectile *p : projectiles)
	//	p->PostRender();
}

bool PistolShot::LevelUp()
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

bool PistolShot::LevelDown()
{
	if (now_level > 0)
	{
		now_level--;
		return true;
	}
	return false;
}