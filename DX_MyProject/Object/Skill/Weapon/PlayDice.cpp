#include "framework.h"

PlayDice::PlayDice()
	:Weapon(SKILL_ID::PLAY_DICE)
	,isKnockBack(false)
{
	weight = 3;
	skillName = "PLAY DICE";
	levelScripts.push_back("Throw out a die. The number on the dice determines the damage.");
	levelScripts.push_back("Increase damage by 30%.");
	levelScripts.push_back("Throw 2 dice.");
	levelScripts.push_back("Dice shoots out farther, and increase area of attack by 30%.");
	levelScripts.push_back("Adds small knockback on hit.");
	levelScripts.push_back("Increase damage by 30%.");
	levelScripts.push_back("Throw 3 dice.");

	skillDelayTable = { 0, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f };
	minDamageTable = { 0,2,3,3,3,3,4,8 };
	maxDamageTable = { 0,6,7,7,7,7,4,8 };
	projCntTalbe = { 0, 1, 1, 2, 2, 2, 2, 3 };
	projSpdTable = { 0,1600,1600,1600,1900,1900,1900,1900 };
	projDelay = 0.5f;
	hitLimitTable = { 0, 4, 4, 4, 4, 4, 4, 4 };	// ù �浹 1, ��ź 3
	colliderIdxTable = { 0,0,0,0,1,1,1,1 };
	ricochetTable = { 0,3,3,3,3,3,3,3 };
	targetDistTable = { 0,200.0f,200.0f,200.0f,250.0f,250.0f,250.0f,250.0f };

	weaponType = WEAPON_TYPE::MULTI_SHOT;

	// �⺻������ �Ѿ��� 10�� �������� ���� ��Ȱ��
	for (int i = 0; i < 10; i++)
	{
		projectiles.push_back(new BaelzDice(Vector2(36.0f, 36.0f)));
		projectiles[i]->SetOwner(this);
	}
	enhanceDamage = 0.0f;
}

PlayDice::~PlayDice()
{
}

void PlayDice::Update()
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
			switch ((int)(projCntTalbe[nowLevel]))
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

			// ����ü �߻簡 �������� ��ų�� ���� ��� ���·�
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
	if (nowLevel == 0)return;

	for (auto p : projectiles)
	{
		p->Render();
	}
}

void PlayDice::PostRender()
{
	if (nowLevel == 0)return;

	ImGui::Text("BaelzDice's skill level : %d", nowLevel);
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
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
	}
	else if (nowLevel == 5)
	{
		isKnockBack = true;
	}
	return true;
}

bool PlayDice::LevelDown()
{
	if (nowLevel > 0)
	{
		nowLevel--;
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

void PlayDice::SpawnProjectile(Vector2 dir)
{
	BaelzDice* proj = GetProjectTile<BaelzDice>();
	int diceEye = GetDiceEye();
	float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], (maxDamageTable[nowLevel] + 1))
		* diceEye // �ֻ��� �� ��ŭ�� �⺻ �������� ���Ѵ�
		* (1 + SkillManager::Get()->addMainWeaponDmgRate + SkillManager::Get()->damageRateShot)
		+ player->GetATK()
		+ enhanceDamage;
	proj->SetStatus(damage, projSpdTable[nowLevel], hitLimitTable[nowLevel], 2.0f);
	proj->SetDirection(dir);
	if (nowLevel == maxLevel)
	{
		proj->ActiveAwaken();
	}
	proj->SetClipIdx(diceEye - 1);
	proj->SetColliderIdx(colliderIdxTable[nowLevel] + player->GetColIdxShot());
	proj->SetRicochetInfo(true, ricochetTable[nowLevel]);
	proj->SetKnockBack(isKnockBack);
	proj->pos = player->pos + dir * 50.0f;
	proj->rot.z = atan(dir.y / dir.x);
	proj->SetTargetDist(targetDistTable[nowLevel]);
	proj->respwan();
}
