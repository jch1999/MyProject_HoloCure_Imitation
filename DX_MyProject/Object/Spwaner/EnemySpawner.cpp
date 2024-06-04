#include "framework.h"

EnemySpawner::EnemySpawner()
	:maxSpawnCnt(0),idx_maxSpawnCnt(0),spawnCnt(0),idx_spawnCnt(0)
	,nowSpawnCnt(0)
	,nowTime(0.0f),endTime(600.0f)
	,spawnDelay(1.5f)
	,fixedInterval(FIXED_INTERVAL),nowInterval(FIXED_INTERVAL)
	,defeatCnt(0)
{
	// Normal Enemey
	// �� ENEMY_NAME�� ���� ���� ���� �ð� ����
	spawnStartTime = {
		0.0f,	// Shrimp
		30.0f,	// DeadBeat
		180.0f,	// Takodachi
		240.0f,	// KFP Employee
		300.0f, // Dark Shrimp
		300.0f, // Bloom
		300.0f, // Gloom
		355.0f,	// DeadBatter
		390.0f,	// Investi-Gator
		455.0f,	// HungryTakodachi
		570.0f // Disgruntled Employee
	};
	// �� ENEMY_NAME�� ���� ���� ���� �ð� ����
	spawnLimitTime = {
		300.0f,	// Shrimp
		300.0f,	// DeadBeat
		300.0f,	// Takodachi
		360.0f,	// KFP Employee
		510.0f, // Dark Shrimp
		660.0f, // Bloom
		660.0f, // Gloom
		510.0f,	// DeadBatter
		660.0f,	// Investi-Gator
		660.0f,	// HungryTakodachi
		660.0f // Disgruntled Employee
	};
	// ���� �ð��� �����ϴ� ������ ENEMY_NAME ����
	enemy_name_list =
	{
		Enemy::ENEMY_NAME::SHRIMP,
		Enemy::ENEMY_NAME::DEADBEAT,
		Enemy::ENEMY_NAME::TAKODACHI,
		Enemy::ENEMY_NAME::KFP_EMPLOYEE,
		Enemy::ENEMY_NAME::DARKSHRIMP,
		Enemy::ENEMY_NAME::BLOOM,
		Enemy::ENEMY_NAME::GLOOM,
		Enemy::ENEMY_NAME::DEADBATTER,
		Enemy::ENEMY_NAME::INVESTI_GATOR,
		Enemy::ENEMY_NAME::HUNGRY_TAKODACHI,
		Enemy::ENEMY_NAME::DISGRUNTLED_EMPLOYEE,
	};
	// �ð� �� �ִ� ���ʹ� �� ����
	maxSpawn_table = {
		{0.0f,50},
		{50.0f,75},
		{100.0f,90},
		{300.0f,120},
		{360.0f,150},
		{480.0f,180},
		{540.0f,210}
	};
	// �ð� �� ���ʹ� ���� �� ����
	spawnCnt_table =
	{
		{0.0f,5},
		{60.0f,10},
		{120.0f,15},
		{240.0f,20},
		{480.0f,40},
		{500.0f,50},
		{540.0f,55}
	};
	spawnCnt = spawnCnt_table[idx_spawnCnt].second;
	maxSpawnCnt = maxSpawn_table[idx_maxSpawnCnt].second;

	// ������ 50�� �̸� �����ϰ� �����ϸ� �߰� ����
	for (int i = 0; i < 10; i++)
	{
		enemy_list.push_back(new Shrimp());
		enemy_list.push_back(new DeadBeat());
		enemy_list.push_back(new Takodachi());
		enemy_list.push_back(new KFP());
		enemy_list.push_back(new Investi());
		enemy_list.push_back(new BloomGloom());
	}

	// Mini Boss
	int size = (int)Enemy::ENEMY_NAME::MEGA_Q_SHRIMP - (int)Enemy::ENEMY_NAME::MEGA_SHRIMP;
	for (int i = 0; i < size; i++)
		miniBossName_list.push_back(Enemy::ENEMY_NAME((int)Enemy::ENEMY_NAME::MEGA_SHRIMP + i));
	miniBossSpawn_idx = 0;
	miniBossSpawnTime_table = { 120.0f,240.0f,360.0f,480.0f,900.0f };

	// �⺻ miniBoss�� 2ü - �ѹ��� ���� �����Ǵ� �ִ� ���� 2, �������ִ°� �ִٸ� ���� ���� �ʿ�
	enemy_list.push_back(new MiniBoss());
	enemy_list.push_back(new MiniBoss());
}

EnemySpawner::~EnemySpawner()
{
	for (auto e : enemy_list)
		delete e;
}

Enemy::ENEMY_ID EnemySpawner::NameToID(Enemy::ENEMY_NAME name)
{
	switch (name)
	{
	case Enemy::ENEMY_NAME::SHRIMP:
	case Enemy::ENEMY_NAME::DARKSHRIMP:
	case Enemy::ENEMY_NAME::Q_SHRIMP_A:
	case Enemy::ENEMY_NAME::Q_SHRIMP_B:
	case Enemy::ENEMY_NAME::RIOT_Q_SHRIMP:
		return Enemy::ENEMY_ID::SHRIMP;
		break;
	case Enemy::ENEMY_NAME::DEADBEAT:
	case Enemy::ENEMY_NAME::DEADBATTER:
	case Enemy::ENEMY_NAME::Q_DEADBEAT_A:
	case Enemy::ENEMY_NAME::Q_DEADBEAT_B:
	case Enemy::ENEMY_NAME::RIOT_DEADBEAT:
	case Enemy::ENEMY_NAME::RIOT_Q_DEADBEAT:
		return Enemy::ENEMY_ID::DEAD_BEAT;
		break;
	case Enemy::ENEMY_NAME::TAKODACHI:
	case Enemy::ENEMY_NAME::HUNGRY_TAKODACHI:
		return Enemy::ENEMY_ID::TAKODACHI;
		break;
	case Enemy::ENEMY_NAME::KFP_EMPLOYEE:
	case Enemy::ENEMY_NAME::DISGRUNTLED_EMPLOYEE:
		return Enemy::ENEMY_ID::KFP;
		break;
	case Enemy::ENEMY_NAME::INVESTI_GATOR:
		return Enemy::ENEMY_ID::INVESTI;
		break;
	case Enemy::ENEMY_NAME::BLOOM:
	case Enemy::ENEMY_NAME::GLOOM:
		return Enemy::ENEMY_ID::BLOOM_GLOOM;
		break;
	default:
		break;
	}
}

Enemy* EnemySpawner::CreateEnemy(Enemy::ENEMY_ID id)
{
	switch (id)
	{
	case Enemy::ENEMY_ID::SHRIMP:
	{
		enemy_list.push_back(new Shrimp());
	}
		break;
	case Enemy::ENEMY_ID::DEAD_BEAT:
	{
		enemy_list.push_back(new DeadBeat());
	}
		break;
	case Enemy::ENEMY_ID::TAKODACHI:
	{
		enemy_list.push_back(new Takodachi());
	}
		break;
	case Enemy::ENEMY_ID::KFP:
	{
		enemy_list.push_back(new KFP());
	}
		break;
	case Enemy::ENEMY_ID::INVESTI:
	{
		enemy_list.push_back(new Investi());
	}
		break;
	case Enemy::ENEMY_ID::BLOOM_GLOOM:
	{
		enemy_list.push_back(new BloomGloom());
	}
		break;
	default:
		break;
	}
	return enemy_list[enemy_list.size() - 1];
}

void EnemySpawner::SpawnNormalEnemy()
{
	// �ð� ����� ���� ���� ����Ʈ ����
	for (int i = 0; i < spawnStartTime.size(); i++)
	{
		if (nowTime - DELTA <= spawnStartTime[i] && nowTime > spawnStartTime[i])
			now_spawn_list.push_back(enemy_name_list[i]);
	}
	for (int i = 0; i < spawnLimitTime.size(); i++)
	{
		if (nowTime - DELTA <= spawnLimitTime[i] && nowTime > spawnLimitTime[i])
			now_spawn_list.remove(enemy_name_list[i]);
	}

	// �Ϲ� Enemy ����
	// ���� ������ üũ
	if (nowDelay >= spawnDelay)
	{
		// ������ ����ŭ ����
		int cnt = spawnCnt > (maxSpawnCnt - nowSpawnCnt) ? (maxSpawnCnt - nowSpawnCnt) : spawnCnt;
		
		if (cnt == 0)return;

		for (int i = 0; i < cnt; i++)
		{
			// ������ �� ����
			Enemy* spawnTarget = nullptr;
			int name_idx = Random::Get()->GetRandomInt(0, now_spawn_list.size()-1);
			list<Enemy::ENEMY_NAME>::iterator iter = now_spawn_list.begin();
			for (int i = 0; i < name_idx; i++)
			{
				iter++;
			}
			Enemy::ENEMY_NAME name = *iter;
			// list���� ���� enemy�� �����ϴ��� �˻�
			for (auto e : enemy_list)
			{
				if ((!(e->is_active))&& e->name == name)
				{
					spawnTarget = e;
					break;
				}
			}
			// ���� ���� ������ ���� ����� �߰�
			if (spawnTarget == nullptr)
			{
				spawnTarget = CreateEnemy(NameToID(name));
				spawnTarget->SetPlayer(player);
			}

			// ���� ��ġ ���� - ī�޶� �ۿ��� ����
			
			// Ȱ��ȭ
			spawnTarget->SetEnemyName(name);
			SetPos(spawnTarget);
			spawnTarget->Respawn();

			nowSpawnCnt++;
		}

		nowDelay = 0.0f;
	}
}

void EnemySpawner::SpawnSpecialEnemy()
{
}

void EnemySpawner::SpawnMiniBoss()
{
	if (miniBossSpawn_idx >= miniBossSpawnTime_table.size())return;

	if (nowTime > miniBossSpawnTime_table[miniBossSpawn_idx])
	{
		Enemy* miniBoss = nullptr;
		for (auto e : enemy_list)
		{
			if (e->id == Enemy::ENEMY_ID::MINI_BOSS && !e->is_active)
			{
				miniBoss = e;
				break;
			}
		}

		if (miniBoss == nullptr)
		{
			miniBoss = new MiniBoss();
			enemy_list.push_back(miniBoss);
		}
		miniBoss->SetEnemyName(miniBossName_list[miniBossSpawn_idx]);
		SetPos(miniBoss);
		miniBoss->Respawn();
		miniBossSpawn_idx++;
	}
}

void EnemySpawner::SpawnBoss()
{
}

void EnemySpawner::SetPos(Enemy *e)
{
	int dir = Random::Get()->GetRandomInt(0, 3);
	float xDist = WIN_CENTER_X + 100.0f;
	float yDist = WIN_CENTER_Y + 100.0f;
	switch (dir)
	{
	case 0:	// ��
	{
		int x = Random::Get()->GetRandomInt(-xDist, xDist + 1);
		e->pos = Vector2(player->pos.x + x, player->pos.y - yDist);
	}
		break;
	case 1: // �Ʒ�
	{
		Vector2 newPos;
		int x = Random::Get()->GetRandomInt(-xDist, xDist + 1);
		e->pos = Vector2(player->pos.x + x, player->pos.y + yDist);
	}
		break;
	case 2: // ����
	{
		Vector2 newPos;
		int y = Random::Get()->GetRandomInt(-yDist, yDist + 1);
		e->pos = Vector2(player->pos.x - xDist, player->pos.y + y);
	}
		break;
	case 3: // ������
	{
		Vector2 newPos;
		int y = Random::Get()->GetRandomInt(-yDist, yDist + 1);
		e->pos = Vector2(player->pos.x + xDist, player->pos.y + y);
	}
		break;
	}
}

void EnemySpawner::Update()
{
	if (isPause||!player->is_active)return;

	nowTime += DELTA;
	nowDelay += DELTA;

	nowInterval -= DELTA;

	// �Ϲ� Enemy �ִ� ���� �� ����
	if (idx_maxSpawnCnt < maxSpawn_table.size() - 1)
	{
		if (nowTime >= maxSpawn_table[(idx_maxSpawnCnt + 1)].first)
		{
			idx_maxSpawnCnt++;
			maxSpawnCnt = maxSpawn_table[idx_maxSpawnCnt].second;
		}
	}

	// �Ϲ� Enemy ���� �� ����
	if (idx_spawnCnt < spawnCnt_table.size() - 1)
	{
		if (nowTime >= spawnCnt_table[idx_spawnCnt + 1].first)
		{
			idx_spawnCnt++;
			nowSpawnCnt = spawnCnt_table[idx_spawnCnt].second;
		}
	}
	
	// �Ϲ� ��
	if (nowTime < endTime && nowSpawnCnt < maxSpawnCnt)
	{
		SpawnNormalEnemy();
	}

	// Mini Boss
	SpawnMiniBoss();

	// Enemy update & �浹 ó��
	// Enemey & Enemy
	for (auto e : enemy_list)
	{
		e->SetAdditionalDirection(Vector2(0, 0));
		
		pair<int, int> ePos = make_pair(e->pos.x / CELL_X, e->pos.y / CELL_Y);
		list<Enemy*> enemyList = GetPartition(ePos);
		for (auto e2 : enemyList)
		{
			if (!e2->is_active)continue;
			if (e == e2)continue;

			float minDist = (e->GetAttackCollider()->Size().GetLength() + e2->GetAttackCollider()->Size().GetLength()) / 1.8f;
			float nowDist = (e->pos - e2->pos).GetLength();
			if (minDist>nowDist)
			{
				Vector2 dir = e->GetAddtionalDirection() + (e->pos - e2->pos).Normalized();
				e->SetAdditionalDirection(dir);
			}
		}
		Vector2 dir = e->GetAddtionalDirection();
		Vector2 dir2;
	}

	// Enemy Update
	for (auto e : enemy_list)
	{
		e->Update();
		Vector2 dir = e->GetAddtionalDirection();
		int a = 0;
	}
	// Enemy & Player
	pair<int, int> pPos = make_pair(player->pos.x / CELL_X, player->pos.y / CELL_Y);
	list<Enemy*> enemyList = GetPartition(make_pair(pPos.first, pPos.second));
	for (auto e : enemyList)
	{
		if (!e->is_active || !e->IsAttackable())continue;

		if (e->GetAttackCollider()->isCollision(player->GetDamageCollider()))
		{
			e->Attack();
		}
	}

	if (nowInterval < 0.0f)
	{
		nowInterval += fixedInterval;
		FixedUpdate();
	}
}

void EnemySpawner::Render()
{
	for (auto e : enemy_list)
	{
		if ((e->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
			e->Render();
	}
}

void EnemySpawner::PostRneder()
{
	for (auto e : enemy_list)
		e->PostRender();
}

void EnemySpawner::SetPlayer(Player* p)
{
	player = p;
	for (auto e : enemy_list)
		e->SetPlayer(player);
}

void EnemySpawner::EnemyDead()
{
	nowSpawnCnt--;
	defeatCnt++;
}

void EnemySpawner::FixedUpdate()
{
	// ���� ���� ����
	partition.clear();

	// ��� Enemy�� �� ĭ�� �°� 
	for (auto e : enemy_list)
	{
		if (!e->is_active)continue;
		int cell_x = (int)(e->pos.x) / CELL_X;
		int cell_y = (int)(e->pos.y) / CELL_Y;
		pair<int, int> ePos = make_pair(cell_x, cell_y);
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				pair<int, int> pos = make_pair(ePos.first + i, ePos.second + j);
				partition[pos].push_back(e);
			}
		}
	}
}