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

	minDamage_table = { 0, 7.0f, 7.0f,10.0f, 10.0f, 10.0f, 12.0f,12.0f };
	maxDamage_table = { 0, 11.0f, 11.0f,14.0f, 14.0f, 14.0f, 16.0f,16.0f };
	colliderIdx_table = { 0, 0, 1, 1, 2, 2, 2, 2 };
	hitCooldown_table = { 0, 0.75f, 0.75f, 0.75f, 0.75f, 0.6f, 0.6f, 0.6f };

	poison = new PoisonArea();

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
	poison->SetColliderIdx(colliderIdx_table[now_level]);
	return true;
}

bool SpiderCooking::LevelDown()
{
	return false;
}

void SpiderCooking::UpdatePoision()
{
	poison->pos = player->pos;
	poison->Update();

	// 충돌 중인 Enemey 검출
	enemyNowFrame.clear();
	removeList.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash의 pos의 CELL 위치를 중앙으로 3x3 영역을 검사
	pair<int, int> sPos = make_pair(poison->pos.x / CELL_X, poison->pos.y / CELL_Y);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first + i, sPos.second + j));
			for (auto e : enemyList)
			{
				if (!e->is_active)continue;
				if (poison->GetCollider()->isCollision(e->GetDamageCollider()))
					enemyNowFrame.push_back(e);
			}
		}
	}

	// 리스트 갱신
	for (auto e : enemyNowFrame)
	{
		auto found = enemyCooltimes.find(e);
		// 기존에 존재하지 않음 - 추가 및 바로 공격하게 설정
		if (found == enemyCooltimes.end())
		{
			enemyCooltimes[e] = 0.0f;
		}
		// 기존에 존재 - 시간 감소
		else
		{
			enemyCooltimes[e] = found->second - DELTA;
		}
	}

	// 시간 경과 체크, coolTime이 지났으면 damage주기
	for (auto m : enemyCooltimes)
	{
		//m.second -= DELTA;
		if (m.second <= 0.0f)
		{
			enemyCooltimes[m.first] = hitCooldown_table[now_level];
			float nowCoolTime = enemyCooltimes[m.first];
			if (player->isCritical())
				{
				m.first->ChangeHP(-(poison->GetDamage()) * 1.5f, true);
			}
			else
			{
				m.first->ChangeHP(-(poison->GetDamage()), false);
			}
			// 이미 죽은 Enemy를 제거 리스트에 추가
			if (!m.first->is_active)
			{
				removeList.push_back(m.first);
			}

		}
	}

	// 제거
	for (auto e : removeList)
	{
		enemyCooltimes.erase(enemyCooltimes.find(e));
	}
}

