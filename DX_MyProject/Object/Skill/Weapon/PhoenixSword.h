#pragma once
class PhoenixSword :public Weapon
{
private:
	vector<float> hitCooldownTable;
	float blazeHitCool;

	// 기존에 충돌한 Enemy 리스트
	map<Enemy*, float> enemyCooltimesB;
	// 이번 프레임에 충돌한 Enemy 리스트
	vector<Enemy*> enemyNowFrameB;
	// 이번 프레임에 충돌하지 않아 제거할 Enemy 리스트
	vector<Enemy*> removeListB;
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