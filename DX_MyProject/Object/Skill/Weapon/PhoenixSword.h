#pragma once
class PhoenixSword :public Weapon
{
private:
	vector<float> hitCooldown_table;
	float blaze_hitCool;

	// 기존에 충돌한 Enemy 리스트
	map<Enemy*, float> enemyCooltimes_b;
	// 이번 프레임에 충돌한 Enemy 리스트
	vector<Enemy*> enemyNowFrame_b;
	// 이번 프레임에 충돌하지 않아 제거할 Enemy 리스트
	vector<Enemy*> removeList_b;
public:
	PhoenixSword();
	~PhoenixSword();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	Blaze* GetBlaze();
};