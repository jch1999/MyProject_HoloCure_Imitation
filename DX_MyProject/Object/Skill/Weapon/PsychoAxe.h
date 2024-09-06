#pragma once
class PsychoAxe :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	vector<Projectile*> axes;

public:
	PsychoAxe();
	~PsychoAxe();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateAxes();
	Axe* GetAxe();
};