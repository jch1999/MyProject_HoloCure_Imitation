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
		COIN, // 범위 내에서 랜덤한 값을 획득
		FOOD, // 체력 회복
		EXP, // 범위 내에서 랜덤한 값을 획득
	}id;
	enum class SKILL_TYPE
	{
		WEAPON, // Enemy를 공격하는 스킬
		BUFFE, // 특수 스텟 상승 or 일정시간 마다 발동
		STAT, // 단순 스텟 상승
		EXTRA // 코인 획득, 경험치 획득 같은 것
	}type;
	enum class SKILL_STATUS
	{
		COOLDOWN,
		PLAY
	}action_status;

	// 스킬 가중치
	int weight;
protected:
	// 투사체에 플레이어를 전달하기 위해 필요
	Player* player;

	int max_level;
	int now_level;

	// 스킬 대기 시간
	vector<float> skillDelay_table;
	float now_skill_delay;
	int idx_skillDelay;
	
	// 활성화 시간
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