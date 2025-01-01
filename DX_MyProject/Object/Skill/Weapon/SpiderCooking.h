#pragma once
class SpiderCooking :public Weapon
{
private:
	PoisonArea* poison;

	vector<float> hitCooldownTable;
	// ������ �浹�� Enemy ����Ʈ
	map<Enemy*, float> enemyCooltimes;
	// �̹� �����ӿ� �浹�� Enemy ����Ʈ
	vector<Enemy*> enemyNowFrame;
	// �̹� �����ӿ� �浹���� �ʾ� ������ Enemy ����Ʈ
	vector<Enemy*> removeList;
	// �浹�� Enemy�� �ǰ� Ƚ��
	map<Enemy*, int> enemyHitCount;

public:
	SpiderCooking();
	~SpiderCooking();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdatePoision();
	float GetDamage();
};