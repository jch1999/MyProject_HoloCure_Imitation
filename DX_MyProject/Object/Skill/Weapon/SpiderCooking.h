#pragma once
class SpiderCooking :public Weapon
{
private:
	PoisonArea* poison;

	vector<float> hitCooldownTable;
	// 기존에 충돌한 Enemy 리스트
	map<Enemy*, float> enemyCooltimes;
	// 이번 프레임에 충돌한 Enemy 리스트
	vector<Enemy*> enemyNowFrame;
	// 이번 프레임에 충돌하지 않아 제거할 Enemy 리스트
	vector<Enemy*> removeList;
	// 충돌한 Enemy의 피격 횟수
	map<Enemy*, int> enemyHitCount;

public:
	SpiderCooking();
	~SpiderCooking();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdatePoision();
	float GetDamage();
};