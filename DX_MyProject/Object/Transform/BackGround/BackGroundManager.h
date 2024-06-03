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
	vector<SunLight*> lights;
private:
	BackGroundManager();
	~BackGroundManager();

	float now_time;

public:
	friend class Singleton;

	void Update();
	void FixedUpdate();
	void Render();
	void AfterRender();
	void PostRneder();

	const vector<Tile*>& GetTileList() { return tiles; }
	void SetPlayer(Player* p);
	Player* GetPlayer() { return player; }
};