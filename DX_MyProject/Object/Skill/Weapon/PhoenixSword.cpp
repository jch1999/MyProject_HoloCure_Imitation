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
	
	weapon_type = WEAPON_TYPE::MELEE;

	minDamage_table = { 0,11.0f, 14.0f,14.0f, 14.0f, 14.0f, 17.0f,5.0f };
	maxDamage_table = { 0,15.0f, 18.0f,18.0f, 18.0f, 18.0f, 21.0f,9.0f };
	colliderIdx_table = { 0,0,0,1,1,1,1,1 };
	hitCooldown_table = { 0,0.33f,0.33f,0.33f,0.33f,0.08f,0.08f,0.07f };
	hitLimit_table = { 0,1,1,1,1,2,2,2 };
	skillDelay_table = { 0, 1.17f, 1.17f, 1.17f, 1.0f, 1.0f, 1.0f, 1.0f };
	blaze_hitCool = 1.0f;

	slash = new KiaraSlash();
	slash->SetOwner(this);
	for (int i = 0; i < 10; i++)
	{
		projectiles.push_back(new Blaze());
		projectiles[i]->SetOwner(this);
	}

	now_skill_delay = 0.0f;
	playTime_table.push_back(1.0f);
	play_time = 0.0f;
	enhanceDamage = 0.0f;
}

PhoenixSword::~PhoenixSword()
{
	delete slash;
	/*for (auto b : projectiles)
		delete b;*/
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

	UpdateSlash();
	UpdateBlaze();
}

void PhoenixSword::Render()
{
	if (now_level == 0)return;

	slash->Render();
	for (auto b : projectiles)
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
	
	for (auto b : projectiles)
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
	else if (now_level == 7)
		dynamic_cast<KiaraSlash*>(slash)->SetAwaken(true);
	slash->SetHitLimit(hitLimit_table[now_level]);
	slash->SetCoolDown(hitCooldown_table[now_level]);
	return true;
	
}

void PhoenixSword::UpdateSlash()
{
	slash->pos = player->pos + slash->move_dir * 60.0f;
	slash->Update();
}

void PhoenixSword::UpdateBlaze()
{
	for (auto b : projectiles)
	{
		b->Update();
	}
}

Blaze* PhoenixSword::GetBlaze()
{
	Blaze* blaze = GetProjectTile<Blaze>();
	
	float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
		+ player->GetATK()
		+ enhanceDamage;
	blaze->SetStatus(damage * 0.2f, 0.0f, -1, 5.0f);

	return blaze;
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