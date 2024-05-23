#pragma once
class Skill
{
public:
	enum class SKILL_ID
	{
		// WEAPON SKILL
		PISTOL_SHOT,
		PHOENIX_SWORD,
		PLAY_DICE,
		HOLO_BOMB,
		ELITE_LAVA_BUCKET,
		PSYCHO_AXE,
		SPIDER_COOKING
		// BUFF SKILL
	}id;
	enum class SKILL_TYPE
	{
		WEAPON,
		BUFFE
	}type;
	enum class SKILL_STATUS
	{
		COOLDOWN,
		PLAY
	}action_status;
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