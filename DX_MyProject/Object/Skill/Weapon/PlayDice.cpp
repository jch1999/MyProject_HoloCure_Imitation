#include "framework.h"

PlayDice::PlayDice()
	:Weapon(SKILL_ID::PLAY_DICE)
	,isKnockBack(false)
{
	weight = 3;
	skill_name = "PLAY DICE";
	level_scripts.push_back("Throw out a die. The number on the dice determines the damage.");
	level_scripts.push_back("Increase damage by 30%.");
	level_scripts.push_back("Throw 2 dice.");
	level_scripts.push_back("Dice shoots out farther, and increase area of attack by 30%.");
	level_scripts.push_back("Adds small knockback on hit.");
	level_scripts.push_back("Increase damage by 30%.");
	level_scripts.push_back("Throw 3 dice.");

	skillDelay_table = { 0, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f };
	minDamage_table = { 0,2,3,3,3,3,4,8 };
	maxDamage_table = { 0,6,7,7,7,7,4,8 };
	projCnt_talbe = { 0, 1, 1, 2, 2, 2, 2, 3 };
	projSpd_table = { 0,1600,1600,1600,1900,1900,1900,1900 };
	proj_delay = 0.5f;
	hitLimit_table = { 0, 4, 4, 4, 4, 4, 4, 4 };	// 첫 충돌 1, 도탄 3
	colliderIdx_table = { 0,0,0,0,1,1,1,1 };
	ricochet_table = { 0,3,3,3,3,3,3,3 };
	targetDist_table = { 0,200.0f,200.0f,200.0f,250.0f,250.0f,250.0f,250.0f };

	weapon_type = WEAPON_TYPE::MULTI_SHOT;

	// 기본적으로 총알을 10개 생성시켜 놓고 재활용
	for (int i = 0; i < 10; i++)
	{
		projectiles.push_back(new BaelzDice(Vector2(36.0f, 36.0f)));
	}
	enhanceDamage = 0.0f;
}

PlayDice::~PlayDice()
{
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
			switch ((int)(projCnt_talbe[now_level]))
			{
			case 1:
			{
				SpawnProjectile(player->GetAttackDir());
			}
				break;
			case 2:
			{
				float z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				float z1 = z - 30.0f * M_PI / 180.0f;
				float z2 = z + 30.0f * M_PI / 180.0f;
				if (player->GetAttackDir().x < 0.0f)
				{
					SpawnProjectile(Vector2(-cosf(z1), -sinf(z1)));
					SpawnProjectile(Vector2(-cosf(z2), -sinf(z2)));
				}
				else
				{
					SpawnProjectile(Vector2(cosf(z1), sinf(z1)));
					SpawnProjectile(Vector2(cosf(z2), sinf(z2)));
				}
			}
				break;
			case 3:
			{
				float z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
				float z1 = z - 30.0f * M_PI / 180.0f;
				float z2 = z + 30.0f * M_PI / 180.0f;
				if (player->GetAttackDir().x < 0.0f)
				{
					SpawnProjectile(Vector2(-cosf(z1), -sinf(z1)));
					SpawnProjectile(Vector2(-cosf(z2), -sinf(z2)));
				}
				else
				{
					SpawnProjectile(Vector2(cosf(z1), sinf(z1)));
					SpawnProjectile(Vector2(cosf(z2), sinf(z2)));
				}
				SpawnProjectile(player->GetAttackDir());
			}
				break;
			default:
				break;
			}

			// 투사체 발사가 끝났으니 스킬은 재사용 대기 상태로
			projCnt = 0;
			action_status = SKILL_STATUS::COOLDOWN;
		}
	}
	break;
	default:
		break;
	}

	for (auto d:projectiles)
	{
		d->Update();
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
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
	}
	else if (now_level == 5)
	{
		isKnockBack = true;
	}
	return true;
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

BaelzDice* PlayDice::GetDice()
{
	BaelzDice* proj = nullptr;
	for (int i = 0; i < projectiles.size(); i++)// 비활성화 상태인 주사위 하나를 찾아 사용
	{
		if (projectiles[i]->is_active == false)
		{
			proj = dynamic_cast<BaelzDice*>(projectiles[i]);
			break;
		}
	}

	// 비활성 상태 주사위 없음 -> 새로 생성
	if (proj == nullptr)
	{
		proj = new BaelzDice(Vector2(36.0f, 36.0f));
		projectiles.push_back(proj);
	}
	return proj;
}

void PlayDice::SpawnProjectile(Vector2 dir)
{
	BaelzDice* proj = GetDice();
	int diceEye = GetDiceEye();
	float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], (maxDamage_table[now_level] + 1))
		* diceEye // 주사위 눈 만큼을 기본 데미지에 곱한다
		* (1 + SkillManager::Get()->add_MainWeapon_dmgRate + SkillManager::Get()->damageRate_Shot)
		+ player->GetATK()
		+ enhanceDamage;
	proj->SetStatus(damage, projSpd_table[now_level], hitLimit_table[now_level], 2.0f);
	proj->SetDirection(dir);
	int clip_idx = max_level == now_level ? 6 + diceEye - 1 : diceEye - 1;
	proj->SetClipIdx(clip_idx);
	proj->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxShot());
	proj->SetRicochetInfo(true, ricochet_table[now_level]);
	proj->SetKnockBack(isKnockBack);
	proj->pos = player->pos + dir * 50.0f;
	proj->rot.z = atan(dir.y / dir.x);
	proj->SetTargetDist(targetDist_table[now_level]);
	proj->respwan();
}
