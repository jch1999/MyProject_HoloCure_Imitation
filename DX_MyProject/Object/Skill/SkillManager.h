#pragma once
#pragma once
class SkillManager :public Singleton<SkillManager>
{
private:
	Player* player;

public:
	vector<Skill*> skill_table; // 전체 스킬 테이블

	vector<Skill*> nowWeapon_list;
	vector<Skill*> nowBuff_list;
	int weaponCnt;
	int buffCnt;
	int total_weight_W;
	int total_weight_B;
	int total_weight_S;
	int total_weight_E;

	// About Skill Effect
	bool isHealDoubled;
	bool nurseHron_active;
	float add_expRate;
	float add_MainWeapon_dmgRate;
	float add_Weapon_dmgRate;
	// Weapon type별 damage 증가량
	float damageRate_Melee;
	float damageRate_Shot;
	float damageRate_Range;
	// 0 weapon 1 buff 2 stat 3 extra
	vector<vector<Skill*>> levelUpAble_list;

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
	void Update_LevelUpAlbeList();
	int GetLevelUpSkillID();
	int GetLevelUpSkillID_W();
	int GetLevelUpSkillID_B();
	int GetLevelUpSkillID_S();
	int GetLevelUpSkillID_E();
	void LevelUp(Skill::SKILL_ID id);
	void Enhance(Skill::SKILL_ID id, float enhanceAmount=0.0f); // 강화 = LevelUp or damageUp
};