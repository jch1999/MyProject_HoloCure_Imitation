#pragma once
class PlayDice :public Weapon
{
private:
	bool isKnockBack;
	vector<float> knockbackSpeed_table, targetDist_table;
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