#include "framework.h"

SpiderCooking::SpiderCooking()
	:Weapon(Skill::SKILL_ID::SPIDER_COOKING)
	,poison(nullptr)
{
	weight = 4;
	skillName = "SPIDER COOKING";
	levelScripts.push_back("Create an area of miasma around, dealing slow damage to enemies inside.");
	levelScripts.push_back("Increase area by 15%.");
	levelScripts.push_back("Increase damage by 30%.");
	levelScripts.push_back("Increase area by 25%.");
	levelScripts.push_back("Increase frequency of hits by 20%.");
	levelScripts.push_back("Increase damage by 60%.");
	levelScripts.push_back("Add small knockback on hit.(not Implemented)");
	
	weaponType = WEAPON_TYPE::MELEE;
	id = SKILL_ID::SPIDER_COOKING;

	minDamageTable = { 0, 7.0f, 7.0f,10.0f, 10.0f, 10.0f, 12.0f,12.0f };
	maxDamageTable = { 0, 11.0f, 11.0f,14.0f, 14.0f, 14.0f, 16.0f,16.0f };
	colliderIdxTable = { 0, 0, 1, 1, 2, 2, 2, 2 };
	hitCooldownTable = { 0, 0.75f, 0.75f, 0.75f, 0.75f, 0.6f, 0.6f, 0.6f };

	poison = new PoisonArea();
	poison->SetOwner(this);

	nowSkillDelay = 0.0f;
	playTimeTable.push_back(1.0f);
	playTime = 0.0f;
	enhanceDamage = 0.0f;
}

SpiderCooking::~SpiderCooking()
{
	delete poison;
}

void SpiderCooking::Update()
{
	if (nowLevel == 0)return;

	UpdatePoision();
}

void SpiderCooking::Render()
{
	if (nowLevel == 0)return;

	poison->Render();
}

void SpiderCooking::PostRender()
{
}

bool SpiderCooking::LevelUp()
{
	if (nowLevel == maxLevel)return false;

	nowLevel++;
	if (nowLevel == 1)
	{
		SkillManager::Get()->nowWeaponList[SkillManager::Get()->weaponCnt++] = this;
		poison->SetActive(true);
		poison->GetCollider()->SetActive(true);
	}
	else if (nowLevel == 7)
		poison->SetKnockBack(true);
	poison->SetColliderIdx(colliderIdxTable[nowLevel]);
	return true;
}

bool SpiderCooking::LevelDown()
{
	return false;
}

void SpiderCooking::UpdatePoision()
{
	poison->SetCoolDown(hitCooldownTable[nowLevel]);
	poison->pos = player->pos;
	poison->Update();
	poison->OnCollision();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash�� pos�� CELL ��ġ�� �߾����� 3x3 ������ �˻�
	// EnemySpawner���� ��� cell�� �������� 3x3 ũ�⿡ ���ԵǴ� ���� ������ �����ߴµ� ���⼭
	// �� 3x3���� �˻��ϸ� 9�� ������?
	
}

float SpiderCooking::GetDamage()
{
	float damage = Random::Get()->GetRandomInt(minDamageTable[nowLevel], maxDamageTable[nowLevel] + 1)
				* (1 + SkillManager::Get()->addWeaponDmgRate + SkillManager::Get()->damageRateMelee)
				+ player->GetATK()
				+ enhanceDamage;
	return damage;
}

