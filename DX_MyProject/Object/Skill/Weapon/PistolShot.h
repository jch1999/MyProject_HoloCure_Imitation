#pragma once
class PistolShot :public Weapon
{
private:

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