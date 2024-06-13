#pragma once
class ItemSpawner :public Singleton<ItemSpawner>
{
private:
	Player* player;

public:
	// 전체 Item의 리스트
	vector<Item*> item_list;

	// Spacial Partitioning? 
	map<pair<int, int>, list<Item*>> partition;

	float nowTime;

	// 모루 생성 확률 및 사용가능 횟수
	float anvilDefualt;
	float anvilDropRate;
	int anvilUseCnt;
	float enhanceDmg;

	// EXP 자석 생성 확률
	float magnetDropRate;

	// Coin 생성 확률
	float coinDefault;
	float coinRate;
	// 획득 가능한 코인량
	float coinValueDefault;
	float coinValue;
	// 현재 획득한 코인 량
	int nowCoinValue;
	bool isCoinAutoPick;

	// Food 생성 확률
	float foodDefault;
	float foodRate;

private:
	ItemSpawner();
	~ItemSpawner();

public:
	friend class Singleton;

	void Update();
	void FixedUpdate();
	void Render();
	void PostRneder();

	const vector<Item*>& GetItemList() { return item_list; }
	void SetPlayer(Player* p);
	// value = 강화 횟수 or EXP 양
	void GenerateItem(Vector2 pos, int value);
	void GenerateItem(Vector2 pos, Item::ITEM_ID id, int value);
	void AddItem(Item* item) { item_list.push_back(item); }

	const list<Item*>& GetPartition(pair<int, int> pos) { return partition[pos]; }
};