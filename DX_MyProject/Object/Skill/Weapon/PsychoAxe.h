#pragma once
class PsychoAxe :public Weapon
{
private:
	// 기존에 충돌한 Enemy 리스트
	vector<list<pair<Enemy*, float>>> enemyCooltimes;
	// 이번 프레임에 충돌한 Enemy 리스트
	vector<Enemy*> enemyNowFrame;
	// 이번 프레임에 충돌하지 않아 제거할 Enemy 리스트
	vector<pair<Enemy*, float>> removeList;

	float rotSpeed;
	float speed;

public:
	PsychoAxe();
	~PsychoAxe();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateAxes();
};