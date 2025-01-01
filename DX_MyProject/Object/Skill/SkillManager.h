#pragma once
#pragma once
class SkillManager :public Singleton<SkillManager>
{
private:
	Player* player;

public:
	vector<Skill*> skillTable; // ��ü ��ų ���̺�

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
	// Weapon type�� damage ������
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

	// Update�� Render�� �ʿ���� -> �ʿ��Ѱ�? ȹ���� �� �ִ� ��ų ����Ʈ�� �� Update���� ����
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
	//void Enhance(Skill::SKILL_ID id, float enhanceAmount=0.0f); // ��ȭ = LevelUp or damageUp
};