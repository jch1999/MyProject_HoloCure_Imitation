#pragma once
class PlayDice :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	bool isKnockBack;
	// level �� ����ü ��, �ӵ�, hit ���Ѽ�, ���� ������, ��ź Ƚ��, �˹� �ӵ�, �̵� �Ÿ�

	vector<float> projCnt_talbe;
	vector<float> projSPD_table;
	vector<int> hitLimt_table;
	vector<float> delay_table;
	vector<int> ricochet_table;
	vector<float> knockbackSpeed_table;
	vector<int> colliderIdx_table;
	vector<float> targetDist_table;

	// ��ų���� ����ϴ� projectile
	vector<Projectile*> projectiles;
	vector<int> ricochetCnt; // �� źȯ�� ��źȽ��
	vector<vector<Enemy*>> hitEnemies; // �ߺ� �浹�� ���� ���� �浵�� ���ʹ��� ������ ����
public:
	PlayDice();
	~PlayDice();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	// Weapon��(��) ���� ��ӵ�
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	int GetDiceEye();
	Projectile* GetTargetProj();
};