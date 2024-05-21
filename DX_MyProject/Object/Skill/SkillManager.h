#pragma once
#pragma once
class SkillManager :public Singleton<SkillManager>
{
private:
	Player* player;

public:
	vector<Skill*> skill_table; // ��ü ��ų ���̺�

	list<Skill*> nowWeapon_list;
	list<Skill*> nowBuff_list;
	int weaponCnt;
	int buffCnt;

	list<Skill*> enhanceAble_list;
	list<Skill*> levelUpAble_list;

private:
	SkillManager();
	~SkillManager();

public:
	friend class Singleton;

	// Update�� Render�� �ʿ���� -> �ʿ��Ѱ�? ȹ���� �� �ִ� ��ų ����Ʈ�� �� Update���� ����
	void Update();
	void Render();
	
	void PostRneder();

	const list<Skill*>& GetEnhaceAbleList();
	const list<Skill*>& GetLevelUpAlbeList();
	Skill* GetSkillByID(Skill::SKILL_ID id);

	void SetPlayer(Player* p);
	void LevelUp(Skill::SKILL_ID id);
	void Enhance(Skill::SKILL_ID id, float enhanceAmount=0.0f); // ��ȭ = LevelUp or damageUp
};