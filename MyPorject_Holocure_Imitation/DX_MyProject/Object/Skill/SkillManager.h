#pragma once
#pragma once
class SkillManager :public Singleton<SkillManager>
{
private:
	Player* player;

public:
	vector<Skill*> skill_table; // 전체 스킬 테이블

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

	// Update나 Render는 필요없음 -> 필요한가? 획득할 수 있는 스킬 리스트를 매 Update마다 갱신
	void Update();
	void Render();
	
	void PostRneder();

	const list<Skill*>& GetEnhaceAbleList();
	const list<Skill*>& GetLevelUpAlbeList();
	Skill* GetSkillByID(Skill::SKILL_ID id);

	void SetPlayer(Player* p);
	void LevelUp(Skill::SKILL_ID id);
	void Enhance(Skill::SKILL_ID id, float enhanceAmount=0.0f); // 강화 = LevelUp or damageUp
};