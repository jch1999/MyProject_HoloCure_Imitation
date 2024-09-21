#pragma once
class Weapon :public Skill
{
public:
	enum class WEAPON_TYPE
	{
		MULTI_SHOT,		// 다중 발사형 - 갯수 증가에 영향을 받음
		RANGE,			// 단순 발사형
		MELEE			// 근접 공격형
	}weapon_type;

protected:
	// 투사체의 설정값이 레벨에 상관없이 일정할 때 사용.
	float proj_delay;
	float now_proj_delay;
	float proj_spd;
	int projCnt;
	float hitCooldown;

	// level 당 데미지, 콜라이더 index
	vector<float> minDamage_table;
	vector<float> maxDamage_table;
	vector<int> colliderIdx_table;

	// level 당 투사체 수, 투사체의 hit 제한수, 공격 딜레이, 생존시간
	vector<float> projCnt_talbe;
	vector<float> projDelay_table;
	vector<float> projSpd_table;
	vector<int> hitLimit_table;
	vector<float> delay_table;
	vector<int> ricochet_table;
	vector<float> projLifetime_table;

	// 무기에서 사용하는 projectile
	vector<Projectile*> projectiles;
	vector<int> ricochetCnt; // 각 탄환의 도탄횟수
	//임시 생성
	//vector<set<Enemy*>> hitEnemies; // 중복 충돌을 막기 위해 충도한 에너미의 정보를 저장

public:
	Weapon(SKILL_ID id,int maxLevel=7);
	virtual ~Weapon();
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual bool LevelUp() = 0;
	virtual bool GetEnhanceAble() { return true; }
	virtual bool Enhance();
};