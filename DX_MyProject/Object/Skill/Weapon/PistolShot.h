#pragma once
class PistolShot :public Weapon
{
private:
	Watson* watson;
	float revengeRate;
	float revengeTime, nowTime;
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

	void UpdateBullet();
};