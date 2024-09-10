#include "framework.h"

PsychoAxe::PsychoAxe()
	:Weapon(Skill::SKILL_ID::PSYCHO_AXE)
{
	weight = 3;
	skill_name = "PSYCHO AXE";
	level_scripts.push_back("Throw an axe that spirals outward from the player.");
	level_scripts.push_back("Increase size of axe by 20%. Increase damage of axe by 20%.");
	level_scripts.push_back("Reduce delay between attacks by 20%.");
	level_scripts.push_back("Increase damage by 33%, and size by 20%.");
	level_scripts.push_back("Remove hit limit, and lasts 1 second longer.");
	level_scripts.push_back("Increase attack size by 50%.");
	level_scripts.push_back("Increase damage by 50%.");

	skillDelay_table = { 0,2.0f, 2.0f, 2.0f, 2.0f, 1.6f,1.6f,1.6f };
	minDamage_table = { 0,10.0f,14.0f,14.0f,19.0f,19.0f,19.0f,28.0f };
	maxDamage_table = { 0,14.0f,18.0f,18.0f,23.0f,23.0f,23.0f,34.0f };
	colliderIdx_table = { 0, 0, 1, 1, 2, 2, 3, 3 };
	projCnt_talbe = { 0,1,1,2,2,3,3,4 };
	projLifetime_table = { 0,3.0f,3.0f,3.0f,3.0f,4.0f,4.0f,4.0f };
	proj_spd = 300.0f;
	proj_delay = 0.83f;
	hitLimit_table = { 0,1,1,1,1,-1,-1,-1 };
	hitCooldown = 0.83f;
	

	weapon_type = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	for (int i = 0; i < 10; i++)
	{
		Projectile* axe = new Axe();
		projectiles.push_back(axe);

	}
	enhanceDamage = 0.0f;

	rotSpeed = 5.0f;
	speed = 300.0f;
}

PsychoAxe::~PsychoAxe()
{
}

void PsychoAxe::Update()
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
				Axe* proj = GetAxe();

				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
					+ player->GetATK()
					+ enhanceDamage;
				bool isCrt = player->isCritical();
				if (isCrt)
					proj->SetStatus(damage * 1.5f, speed, hitLimit_table[now_level], projLifetime_table[now_level], hitCooldown);
				else
					proj->SetStatus(damage, speed, hitLimit_table[now_level], projLifetime_table[now_level], hitCooldown);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(colliderIdx_table[now_level]);
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->SetRotSpeed(rotSpeed);
				proj->SetCrt(isCrt);
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

	UpdateAxes();
}

void PsychoAxe::Render()
{
	for (auto a : projectiles)
		a->Render();
}

void PsychoAxe::PostRender()
{
	ImGui::SliderFloat("RotSpeed", &rotSpeed, 0.0f, 360.0f);
	ImGui::SliderFloat("Speed", &speed, 0.0f, 1000.0f);
}

bool PsychoAxe::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}

bool PsychoAxe::LevelDown()
{
	return false;
}

void PsychoAxe::UpdateAxes()
{
	for (auto axe : projectiles)
	{
		if (axe->is_active)
		{
			axe->Update();
		}
	}
}

Axe* PsychoAxe::GetAxe()
{
	Axe* axe = nullptr;
	for (int i = 0; i < projectiles.size(); i++)// 비활성화 상태인 폭탄 하나를 찾아 사용
	{
		if (projectiles[i]->is_active == false)
		{
			axe = dynamic_cast<Axe*>(projectiles[i]);
			break;
		}
	}

	// 비활성 상태 도끼 없음 -> 새로 생성
	if (axe == nullptr)
	{
		axe = new Axe();
		projectiles.push_back(axe);
	}
	return axe;
}
