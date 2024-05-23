#pragma once
class EnemySpawner:public Singleton<EnemySpawner>
{
private:
	Player* player;

public:
	int maxSpawnCnt;
	int nowSpawnCnt;
	
	float nowTime;
	float endTime;
	
	float fixedInterval;
	float nowInterval;

	float spawnDelay;
	float nowDelay;

	// �Ϲ� ��
	// �� ���� �� ������ ��
	vector<pair<float, int>> spawnCnt_table;
	int spawnCnt_idx;
	int spawnCnt;
	
	// �ð� ����� ���� �ִ� ���� �� ����
	vector<pair<float, int>> maxSpawn_table;
	int spawn_idx;

	// �� ENEMY_NAME�� �����ϴ� ���� ���� �ð��� ���� ���� �ð�
	vector<float> spawnStartTime;
	vector<float> spawnLimitTime;
	vector<Enemy::ENEMY_NAME> enemy_name_list;	// ��ü �Ϲ� ENEMY_NAME ����Ʈ - ������ ���� ���̴� vector
	list<Enemy::ENEMY_NAME> now_spawn_list;		// ���� ���� ������ ENEMY_NAME ����Ʈ - ���� �߰��� ����� �״� list��

	// special enemy

	// mini boss
	vector<Enemy::ENEMY_NAME> miniBossName_list;
	vector<float> miniBossSpawnTime_table;
	int miniBossSpawn_idx;

	// ��ü Enemy�� ����Ʈ
	vector<Enemy*> enemy_list;

	// Spacial Partitioning? 
	map<pair<int, int>, list<Enemy*>> partition;

private:
	EnemySpawner();
	~EnemySpawner();

	Enemy::ENEMY_ID NameToID(Enemy::ENEMY_NAME name);
	Enemy* CreateEnemy(Enemy::ENEMY_ID id);
	void SpawnNormalEnemy();
	void SpawnSpecialEnemy();
	void SpawnMiniBoss();
	void SpawnBoss();

	void SetPos(Enemy *e);

public:
	friend class Singleton;
	
	void Update();
	void FixedUpdate();
	void Render();
	void PostRneder();

	const vector<Enemy*> &GetEnemyList() { return enemy_list; }
	void SetPlayer(Player* p);
	void EnemyDead() { nowSpawnCnt--; }
	void AddEnemy(Enemy* enemy) { enemy_list.push_back(enemy); }
	const map<pair<int, int>, list<Enemy*>>& GetPartition() { return partition; }
	const list<Enemy*>& GetPartition(pair<int,int> pos) { return partition[pos]; }
};