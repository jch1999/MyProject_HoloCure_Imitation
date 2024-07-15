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
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	// level �� ������, �ݶ��̴� index
	vector<float> minDamage_table;
	vector<float> maxDamage_table;
	vector<int> colliderIdx_table;

	// level �� ����ü ��, ����ü�� hit ���Ѽ�, ���� ������
	vector<float> projCnt_talbe;
	vector<int> hitLimit_table;
	vector<float> delay_table;
	vector<int> ricochet_table;

	// ���⿡�� ����ϴ� projectile
	vector<Projectile*> projectiles;
	vector<int> ricochetCnt; // �� źȯ�� ��źȽ��
	vector<set<Enemy*>> hitEnemies; // �ߺ� �浹�� ���� ���� �浵�� ���ʹ��� ������ ����

public:
	Weapon(SKILL_ID id,int maxLevel=7);
	virtual ~Weapon();
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual bool LevelUp() = 0;
	virtual bool GetEnhanceAble() { return true; }
	virtual bool Enhance();
};