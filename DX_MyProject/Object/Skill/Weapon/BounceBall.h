#pragma once
class BounceBall :public Weapon
{
private:
	vector<float> nowCoolDown;

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
	Ball* GetBall();
};