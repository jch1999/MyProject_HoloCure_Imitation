#pragma once
class BaelzDice :public Projectile
{
protected:
	static vector<vector<shared_ptr<const Frame>>> diceFrmaes;
	static int diceUseCnt;

private:
	bool isAwaken;
	bool isRicochet;
	int ricochetCnt;
	
public:
	BaelzDice(ProjectileSize projSize=ProjectileSize(Vector2(36.0f,36.0f)));
	~BaelzDice();

public:
	// Projectile을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;
	void SetRicochetInfo(bool isRicochet, int inCnt);
	void ActiveAwaken();
	void DeactiveAwken();
};