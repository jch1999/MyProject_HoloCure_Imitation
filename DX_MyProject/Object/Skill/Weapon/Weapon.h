#pragma once
class Weapon :public Skill
{
public:
	enum class WEAPON_TYPE
	{
		MULTI_SHOT,		// ���� �߻��� - ���� ������ ������ ����
		RANGE,			// �ܼ� �߻���
		MELEE			// ���� ������
	}type;
protected:
	// level �� ������, �ݶ��̴� index
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