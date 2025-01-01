#pragma once
#pragma once
class SkillManager :public Singleton<SkillManager>
{
private:
	Player* player;

public:
	vector<Skill*> skillTable; // 전체 스킬 테이블

	vector<Skill*> nowWeaponList;
	vector<Skill*> nowBuffList;
	int weaponCnt;
	int buffCnt;
	int totalWeightW;
	int totalWeightB;
	int totalWeightS;
	int totalWeightE;

	// About Skill Effect
	bool isHealDoubled;
	bool nurseHronActive;
	float addExpRate;
	float addMainWeaponDmgRate;
	float addWeaponDmgRate;
	// Weapon type별 damage 증가량
	float damageRateMelee;
	float damageRateShot;
	float damageRateRange;
	// 0 weapon 1 buff 2 stat 3 extra
	vector<vector<Skill*>> levelUpAbleList;

private:
	SkillManager();
	~SkillManager();

public:
	friend class Singleton;

	// Update나 Render는 필요없음 -> 필요한가? 획득할 수 있는 스킬 리스트를 매 Update마다 갱신
	void Update();
	void Render();
	
	void PostRneder();

	Skill* GetSkillByID(Skill::SKILL_ID id);

	void SetPlayer(Player* p);
	Player* GetPlayer() { return player; }
	void Update_LevelUpAlbeList();
	int GetLevelUpSkillID();
	int GetLevelUpSkillID_W();
	int GetLevelUpSkillID_B();
	int GetLevelUpSkillID_S();
	int GetLevelUpSkillID_E();
	//void LevelUp(Skill::SKILL_ID id);
	//void Enhance(Skill::SKILL_ID id, float enhanceAmount=0.0f); // 강화 = LevelUp or damageUp
};