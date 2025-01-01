#pragma once
class PhoenixSword :public Weapon
{
private:
	vector<float> hitCooldownTable;
	float blazeHitCool;

	// ������ �浹�� Enemy ����Ʈ
	map<Enemy*, float> enemyCooltimesB;
	// �̹� �����ӿ� �浹�� Enemy ����Ʈ
	vector<Enemy*> enemyNowFrameB;
	// �̹� �����ӿ� �浹���� �ʾ� ������ Enemy ����Ʈ
	vector<Enemy*> removeListB;
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