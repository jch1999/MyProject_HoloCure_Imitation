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

	// 일반 몹
	// 적 생성 시 생성할 수
	vector<pair<float, int>> spawnCnt_table;
	int spawnCnt_idx;
	int spawnCnt;
	
	// 시간 경과에 따라 최대 생성 수 변경
	vector<pair<float, int>> maxSpawn_table;
	int spawn_idx;

	// 각 ENEMY_NAME에 대응하는 생성 시작 시간과 생성 종료 시간
	vector<float> spawnStartTime;
	vector<float> spawnLimitTime;
	vector<Enemy::ENEMY_NAME> enemy_name_list;	// 전체 일반 ENEMY_NAME 리스트 - 변경이 없을 것이니 vector
	list<Enemy::ENEMY_NAME> now_spawn_list;		// 현재 생성 가능한 ENEMY_NAME 리스트 - 삭제 추가가 빈번할 테니 list로

	// special enemy

	// mini boss
	vector<Enemy::ENEMY_NAME> miniBossName_list;
	vector<float> miniBossSpawnTime_table;
	int miniBossSpawn_idx;

	// 전체 Enemy의 리스트
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