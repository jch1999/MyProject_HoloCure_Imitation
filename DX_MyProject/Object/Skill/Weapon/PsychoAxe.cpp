#include "framework.h"

PsychoAxe::PsychoAxe()
	:Weapon(Skill::SKILL_ID::PSYCHO_AXE)
{
	weight = 3;
	skillName = "PSYCHO AXE";
	levelScripts.push_back("Throw an axe that spirals outward from the player.");
	levelScripts.push_back("Increase size of axe by 20%. Increase damage of axe by 20%.");
	levelScripts.push_back("Reduce delay between attacks by 20%.");
	levelScripts.push_back("Increase damage by 33%, and size by 20%.");
	levelScripts.push_back("Remove hit limit, and lasts 1 second longer.");
	levelScripts.push_back("Increase attack size by 50%.");
	levelScripts.push_back("Increase damage by 50%.");

	skillDelayTable = { 0, 4.0f, 4.0f, 3.2f, 3.2f, 3.2f, 3.2f, 3.2f };
	minDamageTable = { 0,10.0f,14.0f,14.0f,19.0f,19.0f,19.0f,28.0f };
	maxDamageTable = { 0,14.0f,18.0f,18.0f,23.0f,23.0f,23.0f,34.0f };
	colliderIdxTable = { 0, 0, 1, 1, 2, 2, 3, 3 };
	projCntTalbe = { 0,1,1,2,2,3,3,4 };
	projLifetimeTable = { 0,3.0f,3.0f,3.0f,3.0f,4.0f,4.0f,4.0f };
	projSpd = 300.0f;
	projDelay = 0.83f;
	hitLimitTable = { 0,1,1,1,1,-1,-1,-1 };
	hitCooldown = 0.83f;
	

	weaponType = WEAPON_TYPE::MULTI_SHOT;
	action_status = Skill::SKILL_STATUS::COOLDOWN;

	for (int i = 0; i < 10; i++)
	{
		Projectile* axe = new Axe();
		projectiles.push_back(axe);
		axe->SetOwner(this);
	}
	enhanceDamage = 0.0f;

	rotSpeed = 5.0f;
}

PsychoAxe::~PsychoAxe()
{
}

void PsychoAxe::Update()
{
	if (nowLevel == 0)return;
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		nowSkillDelay += DELTA;
		if (nowSkillDelay >= skillDelayTable[nowLevel])
		{
			action_status = SKILL_STATUS::PLAY;
			nowSkillDelay = 0.0f;
		}
	}
	break;
	case Skill::SKILL_STATUS::PLAY:
	{
		if (nowProjDelay < projDelay)
		{
			nowProjDelay += DELTA;
		}
		else
		{
			nowProjDelay = 0.0f;
			if (projCnt < projCntTalbe[nowLevel] + player->GetProjCnt()) // 투사체를 덜 발사함
			{
				Axe* proj = GetProjectTile<Axe>();

				float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
					* (1 + SkillManager::Get()->addWeaponDmgRate + SkillManager::Get()->damageRateShot)
					+ player->GetATK()
					+ enhanceDamage;
				bool isCrt = player->isCritical();
				if (isCrt)
					proj->SetStatus(damage * 1.5f, projSpd, hitLimitTable[nowLevel], projLifetimeTable[nowLevel], hitCooldown);
				else
					proj->SetStatus(damage, projSpd, hitLimitTable[nowLevel], projLifetimeTable[nowLevel], hitCooldown);
				proj->SetDirection(player->GetAttackDir());
				proj->SetColliderIdx(colliderIdxTable[nowLevel]);
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
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
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
