#pragma once
class ItemSpawner :public Singleton<ItemSpawner>
{
private:
	Player* player;

public:
	// ��ü Item�� ����Ʈ
	vector<Item*> item_list;

	// Spacial Partitioning? 
	map<pair<int, int>, list<Item*>> partition;

	float nowTime;

	// ��� ���� Ȯ�� �� ��밡�� Ƚ��
	float anvilDefualt;
	float anvilDropRate;
	int anvilUseCnt;
	float enhanceDmg;

	// EXP �ڼ� ���� Ȯ��
	float magnetDropRate;

	// Coin ���� Ȯ��
	float coinDefault;
	float coinRate;
	// ȹ�� ������ ���η�
	float coinValueDefault;
	float coinValue;
	// ���� ȹ���� ���� ��
	int nowCoinValue;
	bool isCoinAutoPick;

	// Food ���� Ȯ��
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
	// value = ��ȭ Ƚ�� or EXP ��
	void GenerateItem(Vector2 pos, int value);
	void GenerateItem(Vector2 pos, Item::ITEM_ID id, int value);
	void AddItem(Item* item) { item_list.push_back(item); }

	const list<Item*>& GetPartition(pair<int, int> pos) { return partition[pos]; }
};