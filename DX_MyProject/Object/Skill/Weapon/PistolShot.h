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

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	// Weapon을(를) 통해 상속됨
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateBullet();
};