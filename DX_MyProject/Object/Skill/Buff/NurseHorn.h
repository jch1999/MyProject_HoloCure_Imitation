#pragma once
class NurseHorn :public Buff
{
protected:
	float healAmount;
	float hpRate;
public:
	NurseHorn();
	~NurseHorn();

	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;

	float GetHealAmount() { return healAmount; }
	float GetTargetRate() { return hpRate; }
};