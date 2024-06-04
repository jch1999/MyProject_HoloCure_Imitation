#pragma once
class Weapon :public Skill
{
public:
	enum class WEAPON_TYPE
	{
		MULTI_SHOT,		// 다중 발사형 - 갯수 증가에 영향을 받음
		RANGE,			// 단순 발사형
		MELEE			// 근접 공격형
	}type;
protected:
	// level 당 데미지, 콜라이더 index
	vector<float> minDamage_table;
	vector<float> maxDamage_table;
	vector<int> colliderIdx_table;
	int enhanceLevel;
	float enhanceDamage;

public:
	Weapon(SKILL_ID id,int maxLevel=7);
	virtual ~Weapon();
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual bool LevelUp() = 0;
	virtual bool GetEnhanceAble() { return true; }
	virtual void Enhance(float enhanceAmount = 0.0f) { this->enhanceDamage += enhanceAmount; }
};