#include "framework.h"

CEOTear::CEOTear()
	:Weapon(SKILL_ID::CEO_TEAR)
{
	weight = 2;
	skill_name = "CEO'S TEAR";
	level_scripts.push_back("Fires rapid tears at random targets.");
	level_scripts.push_back("Increases damage by 20%.");
	level_scripts.push_back("Shoot 2 tears.");
	level_scripts.push_back("Reduce the time between attacks by 33%.");
	level_scripts.push_back("Tears are 25% faster and increase damage by 20%.");
	level_scripts.push_back("Reduce the time between attacks by 50%.");
	level_scripts.push_back("Shoot 4 tears.");
	
	skillDelay_table = { 0.0f,0.5f,0.5f,0.5f,0.33f,0.33f,0.17f,0.17f };
	minDamage_table = { 0.0f,8.0f,10.0f,10.0f,10.0f,12.0f,12.0f,12.0f };
	maxDamage_table = { 0.0f,12.0f,14.0f,14.0f,14.0f,16.0f,16.0f,16.0f };
	projCnt_talbe = { 0,1,1,2,2,2,2,4 };
	proj_delay = 0.15f;
	projSpd_table = { 0.0f,200.0f,200.0f,200.0f,200.0f,250.0f,250.0f,250.0f };
	hitLimit_table = { 0,1,1,1,1,1,1,1 };

	weapon_type = WEAPON_TYPE::MULTI_SHOT;

	// 기본적으로 눈물을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 8; i++)
	{
		Projectile* tear = new Tear();
		tear->SetActive(false);
		tear->GetCollider()->SetActive(false);
		tear->SetOwner(this);

		projectiles.push_back(tear);
	}
	enhanceDamage = 0.0f;
}

CEOTear::~CEOTear()
{
	for (auto p : tears)
		delete p;
}

void CEOTear::UpdateTears()
{
	for (auto t : projectiles)
	{
		if (t->is_active)
		{
			t->Update();
		}
	}
}

bool CEOTear::LevelDown()
{
	return false;
}

void CEOTear::Update()
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
				Tear* proj = GetProjectTile<Tear>();

				float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
					* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Shot)
					+ player->GetATK()
					+ enhanceDamage;
				proj->SetStatus(damage, projSpd_table[now_level], hitLimit_table[now_level], 5.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(0);
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
	UpdateTears();
}

void CEOTear::Render()
{
	if (now_level == 0)return;
	for (auto t : projectiles)
		t->Render();
}

void CEOTear::PostRender()
{
}

bool CEOTear::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	return true;
}
