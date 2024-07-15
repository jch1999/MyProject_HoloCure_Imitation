#include "framework.h"

HoloBomb::HoloBomb()
	:Weapon(Skill::SKILL_ID::HOLO_BOMB)
{
	weight = 3;
	skill_name = "HOLO BOMB";
	level_scripts.push_back("A bomb that explodes, dealing damage to all nearby targets.");
	level_scripts.push_back("Increase explosion size by 15%.");
	level_scripts.push_back("Increase damage by 20%.");
	level_scripts.push_back("Throw 2 bombs.");
	level_scripts.push_back("Reduce the time between attacks by 20%.");
	level_scripts.push_back("Increase explosion size by 20%.");
	level_scripts.push_back("Throw 3 bombs.");

	skillDelay_table = { 0,2.0f, 2.0f, 2.0f, 2.0f, 1.6f,1.6f,1.6f };
	minDamage_table = { 0,15.0f,15.0f,15.0f,15.0f,15.0f,18.0f,18.0f };
	maxDamage_table = { 0,19.0f,19.0f,19.0f,19.0f,19.0f,22.0f,22.0f };
	projCnt_talbe = { 0,1,1,1,2, 2,2,3 };
	hitLimit_table = { 0,1,1,1,1,1,1,1 };
	// explosionCollider size table
	colliderIdx_table = { 0,0,1,1,1,1,2,2 };

	type = WEAPON_TYPE::MULTI_SHOT;

	// �⺻������ ��ź�� ���� ȿ���� 20�� �� �������� ���� ��Ȱ��
	for (int i = 0; i < 10; i++)
	{
		Projectile* bomb = new Bomb();
		bomb->SetActive(false);
		bomb->GetCollider()->SetActive(false);

		projectiles.push_back(bomb);

		Projectile* explosion = new ExplosionSmoke();
		explosion->SetActive(false);
		explosion->GetCollider()->SetActive(false);
		explosions.push_back(explosion);

		vector<Enemy*> v;
		hitEnemies.push_back(v);
	}
	enhanceDamage = 0.0f;
}

HoloBomb::~HoloBomb()
{
	for (auto e : explosions)
		delete e;
}

void HoloBomb::Update()
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
			if (projCnt < projCnt_talbe[now_level] + player->GetProjCnt()) // ����ü�� �� �߻���
			{
				Projectile* proj = nullptr;
				for (int i = 0; i < projectiles.size(); i++)// ��Ȱ��ȭ ������ ��ź �ϳ��� ã�� ���
				{
					if (projectiles[i]->is_active == false)
					{
						proj = projectiles[i];
						ricochetCnt[i] = 0;
						hitEnemies[i].clear();
						break;
					}
				}

				// ��Ȱ�� ���� ��ź ���� == ��ź�� ������ -> ���� ����
				if (proj == nullptr)
				{
					proj = new Bomb();
					projectiles.push_back(proj);
					ricochetCnt.push_back(0);
					vector<Enemy*> v;
					hitEnemies.push_back(v);
				}

				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(damage, 250.0f, hitLimit_table[now_level], -1.0f);
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

	UpdateBomb();
	UpdateBombEffect();
}

void HoloBomb::Render()
{
	if (now_level == 0)return;
	for (auto p : projectiles)
	{
		p->Render();
	}
	for (auto e : explosions)
	{
		e->Render();
	}
}

void HoloBomb::PostRender()
{
}

bool HoloBomb::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool HoloBomb::LevelDown()
{
	return false;
}

void HoloBomb::UpdateBomb()
{
}

void HoloBomb::UpdateBombEffect()
{
}
