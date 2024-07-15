#pragma once
class PhoenixSword :public Weapon
{
private:
	vector<float> hitCooldown_table;
	float blaze_hitCool;

	Projectile* slash;
	vector<Projectile*> blazes;

	// 기존에 충돌한 Enemy 리스트
	map<Enemy*, float> enemyCooltimes_s;
	map<Enemy*, float> enemyCooltimes_b;
	// 이번 프레임에 충돌한 Enemy 리스트
	vector<Enemy*> enemyNowFrame_s;
	vector<Enemy*> enemyNowFrame_b;
	// 이번 프레임에 충돌하지 않아 제거할 Enemy 리스트
	vector<Enemy*> removeList_s;
	vector<Enemy*> removeList_b;
	// 충돌한 Enemy의 피격 횟수
	map<Enemy*, int> enemyHitCount;
public:
	PhoenixSword();
	~PhoenixSword();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateSlash();
	void UpdateBlaze();
};