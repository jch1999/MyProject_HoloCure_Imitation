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

	proj_delay = 0.08f;

	weapon_type = WEAPON_TYPE::MULTI_SHOT;

	skillDelay_table = { 0,2.0f, 2.0f, 2.0f, 2.0f, 1.6f,1.6f,1.6f };
	minDamage_table = { 0,15.0f,15.0f,15.0f,15.0f,15.0f,18.0f,18.0f };
	maxDamage_table = { 0,19.0f,19.0f,19.0f,19.0f,19.0f,22.0f,22.0f };
	projCnt_talbe = { 0,1,1,1,2, 2,2,3 };
	proj_spd = 7.0f;
	hitLimit_table = { 0,1,1,1,1,1,1,1 };
	// explosionCollider size table
	colliderIdx_table = { 0,0,1,1,1,1,2,2 };

	weapon_type = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	// �⺻������ ��ź�� ���� ȿ���� 10�� �� �������� ���� ��Ȱ��
	for (int i = 0; i < 10; i++)
	{
		Projectile* bomb = new Bomb();
		projectiles.push_back(bomb);
	}
	enhanceDamage = 0.0f;
}

HoloBomb::~HoloBomb()
{

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
				Bomb* proj = GetBomb();
				
				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
					+ player->GetATK()
					+ enhanceDamage;
				bool isCrt = player->isCritical();
				proj->SetStatus(0.0f, proj_spd, 1, -1.0f,0.0f);
				if (isCrt)
					proj->SetExplosionStatus(damage * 1.5f, 0.0f, hitLimit_table[now_level], -1.0f, 0.0f, isCrt);
				else
					proj->SetExplosionStatus(damage * 1.5f, 0.0f, hitLimit_table[now_level], -1.0f, 0.0f, isCrt);

				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(0);
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->SetTargetPos(proj->pos + player->GetAttackDir() * proj->GetTargetDist());
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
}

void HoloBomb::Render()
{
	if (now_level == 0)return;
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
	for (auto b : projectiles)
	{
		b->Update();
	}
}

Bomb* HoloBomb::GetBomb()
{
	Bomb* bomb = nullptr;
	for (int i = 0; i < projectiles.size(); i++)// ��Ȱ��ȭ ������ ��ź �ϳ��� ã�� ���
	{
		if (projectiles[i]->is_active == false)
		{
			bomb = dynamic_cast<Bomb*>(projectiles[i]);
			break;
		}
	}

	// ��Ȱ�� ���� ��ź ���� == ��ź�� ������ -> ���� ����
	if (bomb == nullptr)
	{
		bomb = new Bomb();
		projectiles.push_back(bomb);
	}
	return bomb;
}