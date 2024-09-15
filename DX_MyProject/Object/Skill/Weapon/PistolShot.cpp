#include "framework.h"

PistolShot::PistolShot()
	:Weapon(SKILL_ID::PISTOL_SHOT)
	, watson(nullptr)
	, revengeRate(0.15f)
	,revengeTime(2.0f),nowTime(0.0f)
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
	level_scripts.push_back("For the next 2 seconds, 15% of all damage taken by target is stored in time. Then target takes total of stored damage.");

	skillDelay_table = { 0,1.33f, 1.33f, 1.33f, 1.33f, 1.0f,1.0f,1.0f };
	minDamage_table = { 0,8,8,10,10,10,12,12 };
	maxDamage_table = { 0,12,12,14,14,14,16,16 };
	projCnt_talbe = { 0,3,5,5,5,5,5,5 };
	proj_spd = 250.0f;
	hitLimit_table = { 0,1,2,2,2,3,3,3 };
	colliderIdx_table = { 0,0,0,0,0,0,0,0 };
	ricochet_table = { 0,0,0,0,1,1,1,1 };

	weapon_type = WEAPON_TYPE::MULTI_SHOT;
	
	// 기본적으로 총알을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		Projectile* bullet = new WatsonBullet(Vector2(30.0f, 24.0f));
		bullet->SetActive(false);
		bullet->GetCollider()->SetActive(false);

		projectiles.push_back(bullet);
	}
	enhanceDamage = 0.0f;
}

PistolShot::~PistolShot()
{
	watson = nullptr;
}

void PistolShot::Update()
{
	if (now_level == 0)return;

	if (watson == nullptr)
	{
		watson = dynamic_cast<Watson*>(player);
	}

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
				WatsonBullet* proj = GetBullet();
				
				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* (1 + SkillManager::Get()->add_MainWeapon_dmgRate + SkillManager::Get()->damageRate_Shot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(damage, proj_spd, hitLimit_table[now_level], 2.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxShot());
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				bool isRicochet = ricochet_table[now_level] > 0;
				proj->SetRicochet(isRicochet, ricochet_table[now_level]);
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


	// 반격
	if (now_level == 7)
	{
		if (nowTime < revengeTime)
			nowTime += DELTA;
		else
		{
			nowTime = 0.0f;
			const list<pair<Enemy*, float>>& revengeList = watson->GetRevnegeList();
			for (auto r : revengeList)
			{
				if (r.first->is_active)
				{
					r.first->ChangeHP(r.second* revengeRate, player->isCritical());
				}
			}
			watson->ClearRevengeList();
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
	else if (now_level == 7)
	{
		watson->SetRevenge(true);
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

void PistolShot::UpdateBullet()
{
	for (auto p : projectiles)
		p->Update();
}

WatsonBullet* PistolShot::GetBullet()
{
	WatsonBullet* proj = nullptr;

	for (int i = 0; i < projectiles.size(); i++)// 비활성화 상태인 총알 하나를 찾아 사용
	{
		if (projectiles[i]->is_active == false)
		{
			proj = dynamic_cast<WatsonBullet*>(projectiles[i]);
			break;
		}
	}

	// 비활성 상태 총알 없음 == 총알이 부족함 -> 새로 생성
	if (proj == nullptr)
	{
		proj = new WatsonBullet(Vector2(30.0f, 24.0f));
		projectiles.push_back(proj);
	}
	return proj;
}
