#pragma once
#pragma once
class SkillManager :public Singleton<SkillManager>
{
private:
	Player* player;

public:
	vector<Skill*> skill_table; // ��ü ��ų ���̺�

	vector<Skill*> nowWeapon_list;
	vector<Skill*> nowBuff_list;
	int weaponCnt;
	int buffCnt;
	int total_weight_W;
	int total_weight_B;
	int total_weight_S;
	int total_weight_E;

	// 0 weapon 1 buff 2 stat 3 extra
	vector<vector<Skill*>> levelUpAble_list;

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
	void Update_LevelUpAlbeList();
	int GetLevelUpSkillID();
	int GetLevelUpSkillID_W();
	int GetLevelUpSkillID_B();
	int GetLevelUpSkillID_S();
	int GetLevelUpSkillID_E();
	void LevelUp(Skill::SKILL_ID id);
	void Enhance(Skill::SKILL_ID id, float enhanceAmount=0.0f); // ��ȭ = LevelUp or damageUp
};