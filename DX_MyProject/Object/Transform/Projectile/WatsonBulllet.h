#pragma once
class WatsonBullet :public Projectile
{
protected:
	static vector<shared_ptr<const Frame>> bulletFrames;
	static int bulletUseCnt;

private:
	Vector2 size;
	bool isRicochet;
	int ricochetCnt;
public:
	WatsonBullet(ProjectileSize porjSize = ProjectileSize(Vector2(30.0f, 24.0f)));
	~WatsonBullet();



	// Projectile을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;
	virtual void Hit() override;


	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;
	void SetRicochet(bool isRicochet, int cnt) { this->isRicochet = isRicochet; ricochetCnt = cnt; }

};