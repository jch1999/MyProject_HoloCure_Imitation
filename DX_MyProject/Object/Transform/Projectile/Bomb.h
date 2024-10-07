#pragma once
class ExplosionSmoke;
class Bomb :public Projectile
{
private:
	float thorwDist;
	Vector2 targetPos;
	ExplosionSmoke* explosion;
	int explosionColiderIdx;

public:
	Bomb(Vector2 size = Vector2(23.0f, 29.0f), float targetDist = 100.0f, Vector2 move_dir = Vector2(0, 0));
	~Bomb();


	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void OnCollision() override;

	virtual void Hit() override;

	void SetTargetPos(Vector2 tPos) { targetPos = tPos; }
	void SetExplosionStatus(float damage, float speed, int hitCount, float lifeTime, float hitCoolDown);
};