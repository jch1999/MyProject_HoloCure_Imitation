#pragma once
class Skill
{
public:
	enum class SKILL_ID
	{
		// WEAPON SKILL
		// defulat
		PISTOL_SHOT,
		PHOENIX_SWORD,
		PLAY_DICE,
		// Weapon
		HOLO_BOMB,
		ELITE_LAVA_BUCKET,
		PSYCHO_AXE,
		BOUNCE_BALL,
		CEO_TEAR,
		SPIDER_COOKING,
		// BUFF SKILL
		NURSE_HORN,
		FULL_MEAL,
		PIKIPIK_PIMAN,
		STUDY_GLASSES,
		SUPER_CHATTO_TIME,
		BLACKSMITH_GEAR,
		NINJA_HEADBAND,
		// STAT SKILL
		MAX_HP,
		ATK,
		SPD,
		CRT,
		PICK_UP,
		// EXTRA
		COIN, // ���� ������ ������ ���� ȹ��
		FOOD, // ü�� ȸ��
		EXP, // ���� ������ ������ ���� ȹ��
	}id;
	enum class SKILL_TYPE
	{
		WEAPON, // Enemy�� �����ϴ� ��ų
		BUFFE, // Ư�� ���� ��� or �����ð� ���� �ߵ�
		STAT, // �ܼ� ���� ���
		EXTRA // ���� ȹ��, ����ġ ȹ�� ���� ��
	}type;
	enum class SKILL_STATUS
	{
		COOLDOWN,
		PLAY
	}action_status;

	// ��ų ����ġ
	int weight;
protected:
	// ����ü�� �÷��̾ �����ϱ� ���� �ʿ�
	Player* player;

	int max_level;
	int now_level;

	// ��ų ��� �ð�
	vector<float> skillDelay_table;
	float now_skill_delay;
	int idx_skillDelay;
	
	// Ȱ��ȭ �ð�
	float play_time;
	vector<float> playTime_table;
	int idx_playTime;
	
	vector<string> level_scripts;

public:
	Skill(SKILL_ID id, SKILL_TYPE type,int maxLevl);
	virtual ~Skill();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	Player* GetPlayer() { return player; }
	void SetPlayer(Player* player) { this->player = player; }

	// LevelUp
	virtual bool LevelUp() = 0;
	virtual bool LevelDown() = 0;
	bool GetLevelUpAble() { return now_level < max_level; }
	// Enhance
	virtual bool GetEnhanceAble() = 0;
	virtual void Enhance(float enhanceAmount=0.0f) = 0;
	int GetLevel() { return now_level; }
};