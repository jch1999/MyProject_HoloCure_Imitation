#include "framework.h"

SpiderCooking::SpiderCooking()
	:Weapon(Skill::SKILL_ID::SPIDER_COOKING)
	,poison(nullptr)
{
	weight = 4;
	skill_name = "SPIDER COOKING";
	level_scripts.push_back("Create an area of miasma around, dealing slow damage to enemies inside.");
	level_scripts.push_back("Increase area by 15%.");
	level_scripts.push_back("Increase damage by 30%.");
	level_scripts.push_back("Increase area by 25%.");
	level_scripts.push_back("Increase frequency of hits by 20%.");
	level_scripts.push_back("Increase damage by 60%.");
	level_scripts.push_back("Add small knockback on hit.(not Implemented)");
	
	weapon_type = WEAPON_TYPE::MELEE;
	id = SKILL_ID::SPIDER_COOKING;

	minDamage_table = { 0, 7.0f, 7.0f,10.0f, 10.0f, 10.0f, 12.0f,12.0f };
	maxDamage_table = { 0, 11.0f, 11.0f,14.0f, 14.0f, 14.0f, 16.0f,16.0f };
	colliderIdx_table = { 0, 0, 1, 1, 2, 2, 2, 2 };
	hitCooldown_table = { 0, 0.75f, 0.75f, 0.75f, 0.75f, 0.6f, 0.6f, 0.6f };

	poison = new PoisonArea();
	poison->SetOwner(this);

	now_skill_delay = 0.0f;
	playTime_table.push_back(1.0f);
	play_time = 0.0f;
	enhanceDamage = 0.0f;
}

SpiderCooking::~SpiderCooking()
{
	delete poison;
}

void SpiderCooking::Update()
{
	if (now_level == 0)return;

	UpdatePoision();
}

void SpiderCooking::Render()
{
	if (now_level == 0)return;

	poison->Render();
}

void SpiderCooking::PostRender()
{
}

bool SpiderCooking::LevelUp()
{
	if (now_level == max_level)return false;

	now_level++;
	if (now_level == 1)
	{
		SkillManager::Get()->nowWeapon_list[SkillManager::Get()->weaponCnt++] = this;
		poison->SetActive(true);
		poison->GetCollider()->SetActive(true);
	}
	else if (now_level == 7)
		poison->SetKnockBack(true);
	poison->SetColliderIdx(colliderIdx_table[now_level]);
	return true;
}

bool SpiderCooking::LevelDown()
{
	return false;
}

void SpiderCooking::UpdatePoision()
{
	poison->SetCoolDown(hitCooldown_table[now_level]);
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
	float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
				* (1 + SkillManager::Get()->add_Weapon_dmgRate + SkillManager::Get()->damageRate_Melee)
				+ player->GetATK()
				+ enhanceDamage;
	return damage;
}

