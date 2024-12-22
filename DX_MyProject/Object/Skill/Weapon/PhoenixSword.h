#pragma once
class PhoenixSword :public Weapon
{
private:
	vector<float> hitCooldown_table;
	float blaze_hitCool;

	// ������ �浹�� Enemy ����Ʈ
	map<Enemy*, float> enemyCooltimes_b;
	// �̹� �����ӿ� �浹�� Enemy ����Ʈ
	vector<Enemy*> enemyNowFrame_b;
	// �̹� �����ӿ� �浹���� �ʾ� ������ Enemy ����Ʈ
	vector<Enemy*> removeList_b;
public:
	PhoenixSword();
	~PhoenixSword();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	Blaze* GetBlaze();
};