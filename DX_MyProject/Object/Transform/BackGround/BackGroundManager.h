#pragma once
class BackGroundManager :public Singleton<BackGroundManager>
{
private:
	Player* player;

public:
	vector<Tile*> tiles;
	vector<Tree*> trees;
	vector<Flower*> flowers;
	vector<Grass*> grasses;
private:
	BackGroundManager();
	~BackGroundManager();


	void SetPos(Tile* t);
	map<pair<int, int>, list<Tile*>> partition;

public:
	friend class Singleton;

	void Update();
	void FixedUpdate();
	void Render();
	void AfterRender();
	void PostRneder();

	const vector<Tile*>& GetTileList() { return tiles; }
	void SetPlayer(Player* p);
	const map<pair<int, int>, list<Tile*>>& GetTile() { return partition; }
	const list<Tile*>& GetPartition(pair<int, int> pos) { return partition[pos]; }
	Player* GetPlayer() { return player; }
};