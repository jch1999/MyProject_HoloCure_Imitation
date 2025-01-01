#pragma once
class PsychoAxe :public Weapon
{
private:
	// ������ �浹�� Enemy ����Ʈ
	vector<list<pair<Enemy*, float>>> enemyCooltimes;
	// �̹� �����ӿ� �浹�� Enemy ����Ʈ
	vector<Enemy*> enemyNowFrame;
	// �̹� �����ӿ� �浹���� �ʾ� ������ Enemy ����Ʈ
	vector<pair<Enemy*, float>> removeList;

	float rotSpeed;
	float speed;

public:
	PsychoAxe();
	~PsychoAxe();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateAxes();
};