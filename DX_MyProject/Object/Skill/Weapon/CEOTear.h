#pragma once
class CEOTear :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	vector<Projectile*> tears;

public:
	CEOTear();
	~CEOTear();


	void UpdateTears();

	// Weapon을(를) 통해 상속됨
	virtual bool LevelDown() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
};