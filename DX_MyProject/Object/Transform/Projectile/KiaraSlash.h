#pragma once
class KiaraSlash :public Projectile
{
private:
	bool isAwaken;

	// 충돌한 Enemy의 피격 횟수
	map<Enemy*, int> enemyHitCount;
public:
	KiaraSlash(ProjectileSize projSize = ProjectileSize(Vector2(162.5f, 160.0f)));
	~KiaraSlash();



	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;
	void SetAwaken(bool awake) { isAwaken = awake; }
};