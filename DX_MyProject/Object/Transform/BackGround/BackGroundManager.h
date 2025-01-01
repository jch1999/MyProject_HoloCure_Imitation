#pragma once
class BackgroundManager :public Singleton<BackgroundManager>
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
	BackgroundManager();
	~BackgroundManager();

	float now_time;

public:
	friend class Singleton;

	void Update();
	void FixedUpdate();
	void BeforeRender();
	void Render();
	void AfterRender();
	void PostRneder();

	const vector<Tile*>& GetTileList() { return tiles; }
	void SetPlayer(Player* p);
	Player* GetPlayer() { return player; }
};