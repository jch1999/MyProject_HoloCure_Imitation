#pragma once
class Weapon :public Skill
{
public:
	enum class WEAPON_TYPE
	{
		MULTI_SHOT,		// ���� �߻��� - ���� ������ ������ ����
		RANGE,			// �ܼ� �߻���
		MELEE			// ���� ������
	}weaponType;

protected:
	// ����ü�� �������� ������ ������� ������ �� ���.
	float projDelay;
	float nowProjDelay;
	float projSpd;
	int projCnt;
	float hitCooldown;

	// level �� ������, �ݶ��̴� index
	vector<float> minDamageTable;
	vector<float> maxDamageTable;
	vector<int> colliderIdxTable;

	// level �� ����ü ��, ����ü�� hit ���Ѽ�, ���� ������, �����ð�
	vector<float> projCntTalbe;
	vector<float> projDelayTable;
	vector<float> projSpdTable;
	vector<int> hitLimitTable;
	vector<float> delayTable;
	vector<int> ricochetTable;
	vector<float> projLifetimeTable;

	// ���⿡�� ����ϴ� projectile
	vector<Projectile*> projectiles;
	vector<int> ricochetCnt; // �� źȯ�� ��źȽ��
	//�ӽ� ����
	//vector<set<Enemy*>> hitEnemies; // �ߺ� �浹�� ���� ���� �浵�� ���ʹ��� ������ ����

public:
	Weapon(SKILL_ID id,int maxLevel=7);
	virtual ~Weapon();
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual bool LevelUp() = 0;
	virtual bool GetEnhanceAble() { return true; }
	virtual bool Enhance();

	template <typename T>
	inline T* GetProjectTile()
	{
		T* proj = nullptr;
		for (int i = 0; i < projectiles.size(); i++)// ��Ȱ��ȭ ������ �Ѿ� �ϳ��� ã�� ���
		{
			if (projectiles[i]->is_active == false)
			{
				proj = dynamic_cast<T*>(projectiles[i]);
				break;
			}
		}

		// ��Ȱ�� ���� Tear ���� == Tear�� ������ -> ���� ����
		if (proj == nullptr)
		{
			proj = new T();
			projectiles.push_back(proj);
			dynamic_cast<Projectile*>(proj)->SetOwner(this);
		}

		return proj;
	}
};
