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

	int maxLevel;
	int nowLevel;

	int enhanceLevel;
	float enhanceRate;
	float enhanceDamage;

	// ��ų ��� �ð�
	vector<float> skillDelayTable;
	float nowSkillDelay;
	int skillDelayIdx;
	
	// Ȱ��ȭ �ð�
	float playTime;
	vector<float> playTimeTable;
	int playTimeIdx;
	
	string skillName;
	vector<string> levelScripts;

public:
	Skill(SKILL_ID id, SKILL_TYPE type,int maxLevl);
	virtual ~Skill();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	Player* GetPlayer() { return player; }
	void SetPlayer(Player* player) { this->player = player; }

	FORCEINLINE const Skill::SKILL_ID GetSkillID() { return id; }
	// LevelUp
	virtual bool LevelUp() = 0;
	virtual bool LevelDown() = 0;
	bool GetLevelUpAble() { return nowLevel < maxLevel; }
	int GetLevel() { return nowLevel; }
	// Enhance
	virtual bool GetEnhanceAble() = 0;
	virtual bool Enhance() = 0;
	FORCEINLINE const int& GetEnhanceLevel() { return enhanceLevel; }
	const int GetEnhanceCost();
	FORCEINLINE const int GetEnhanceRate() { return (int)round(enhanceRate * 100.0f); }
	FORCEINLINE const float& GetEnhanceDamge() { return enhanceDamage; }

	FORCEINLINE const string& GetScript() { return levelScripts[nowLevel]; }
	FORCEINLINE const string& GetSkillName() { return skillName; }
};