#pragma once
class PlayDice :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	bool isKnockBack;
	// level 당 투사체 수, 속도, hit 제한수, 공격 딜레이, 도탄 횟수, 넉백 속도, 이동 거리

	vector<float> projCnt_talbe;
	vector<float> projSPD_table;
	vector<int> hitLimt_table;
	vector<float> delay_table;
	vector<int> ricochet_table;
	vector<float> knockbackSpeed_table;
	vector<int> colliderIdx_table;
	vector<float> targetDist_table;

	// 스킬에서 사용하는 projectile
	vector<Projectile*> projectiles;
	vector<int> ricochetCnt; // 각 탄환의 도탄횟수
	vector<vector<Enemy*>> hitEnemies; // 중복 충돌을 막기 위해 충도한 에너미의 정보를 저장
public:
	PlayDice();
	~PlayDice();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	// Weapon을(를) 통해 상속됨
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	int GetDiceEye();
	Projectile* GetTargetProj();
};