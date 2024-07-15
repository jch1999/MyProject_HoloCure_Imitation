#pragma once
class PhoenixSword :public Weapon
{
private:
	vector<float> hitCooldown_table;
	float blaze_hitCool;

	Projectile* slash;
	vector<Projectile*> blazes;

	// ������ �浹�� Enemy ����Ʈ
	map<Enemy*, float> enemyCooltimes_s;
	map<Enemy*, float> enemyCooltimes_b;
	// �̹� �����ӿ� �浹�� Enemy ����Ʈ
	vector<Enemy*> enemyNowFrame_s;
	vector<Enemy*> enemyNowFrame_b;
	// �̹� �����ӿ� �浹���� �ʾ� ������ Enemy ����Ʈ
	vector<Enemy*> removeList_s;
	vector<Enemy*> removeList_b;
	// �浹�� Enemy�� �ǰ� Ƚ��
	map<Enemy*, int> enemyHitCount;
public:
	PhoenixSword();
	~PhoenixSword();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateSlash();
	void UpdateBlaze();
};