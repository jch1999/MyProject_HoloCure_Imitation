#include "framework.h"

PistolShot::PistolShot()
	:Skill(7,1.33f),proj_delay(0.2f),now_proj_delay(0.0f)
	,projCnt(0)
{
	damage_table = { 0,10,10,12,12,12,14,14 };
	projCnt_talbe = { 0,3,5,5,5,5,5,5 };
	hitLimt_table = { 0,1,2,2,2,3,3,3 };

	// 기본적으로 총알을 50개 생성시켜 놓고 재활용
	for (int i = 0; i < 30; i++)
	{
		WatsonBullet* bullet = new WatsonBullet(Vector2(20.0f, 16.0f));
		bullet->SetActive(false);
		bullet->GetCollider()->SetActive(false);

		projectiles.push_back(bullet);
	}
}

PistolShot::~PistolShot()
{
	
}

void PistolShot::Update()
{
	if (KEY_CON->Down('Y'))
	{
		now_level++;
		if (now_level > max_level)
			now_level = 0;
	}

	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		now_skill_delay += DELTA;
		if (now_skill_delay >= skill_delay)
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
			if (projCnt < projCnt_talbe[now_level]) // 투사체를 덜 발사함
			{
				Projectile* proj = nullptr;
				for (Projectile* p : projectiles)// 비활성화 상태인 총알 하나를 찾아 사용
				{
					if (p->is_active == false)
					{
						proj = p;
						break;
					}
				}

				// 비활성 상태 총알 없음 == 총알이 부족함 -> 새로 생성
				if (proj == nullptr)
				{
					proj = new WatsonBullet(Vector2(30.0f, 24.0f));
					projectiles.push_back(proj);
				}
				proj->respwan();
				proj->SetStatus(damage_table[now_level] + player->GetAttack() , 250.0f, hitLimt_table[now_level], 2.0f);
				proj->SetDirection(player->GetAttackDir());
				proj->pos = player->pos + player->GetAttackDir() * 50.0f;
				proj->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				
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
	for (auto p : projectiles)
	{
		p->Update();
	}
}

void PistolShot::Render()
{
	for (auto p : projectiles)
	{
		p->Render();
	}
}

void PistolShot::PostRender()
{
	ImGui::Text("watsonWeapon's skill level : %d", now_level);

	//for (Projectile *p : projectiles)
	//	p->PostRender();
}
