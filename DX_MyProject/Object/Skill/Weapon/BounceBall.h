#pragma once
class BounceBall :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	vector<Projectile*> balls;

public:
	BounceBall();
	~BounceBall();


	void UpdateBalls();

	// Weapon��(��) ���� ��ӵ�
	virtual bool LevelDown() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
};