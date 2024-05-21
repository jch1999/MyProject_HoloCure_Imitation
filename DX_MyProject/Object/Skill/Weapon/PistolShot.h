#pragma once
class PistolShot :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	// level �� ����ü ��, ����ü�� hit ���Ѽ�, ���� ������
	
	vector<float> projCnt_talbe;
	vector<int> hitLimt_table;
	vector<float> delay_table;
	vector<int> ricochet_table;

	// ��ų���� ����ϴ� projectile
	vector<Projectile*> projectiles;
	vector<int> ricochetCnt; // �� źȯ�� ��źȽ��
	vector<vector<Enemy*>> hitEnemies; // �ߺ� �浹�� ���� ���� �浵�� ���ʹ��� ������ ����
public:
	PistolShot();
	~PistolShot();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	// Weapon��(��) ���� ��ӵ�
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;
};