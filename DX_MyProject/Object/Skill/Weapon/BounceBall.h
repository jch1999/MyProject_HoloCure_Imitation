#pragma once
class BounceBall :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	float hitCooldown;
	int projCnt;
	vector<float> nowCoolDown;
	vector<Projectile*> balls;

public:
	BounceBall();
	~BounceBall();


	void UpdateBalls();

	// Weapon을(를) 통해 상속됨
	virtual bool LevelDown() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	Ball* GetBall();
};