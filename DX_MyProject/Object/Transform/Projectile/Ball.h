#pragma once
class Ball :public Projectile
{
private:
	Vector2 velocity;
public:
	Ball(ProjectileSize projSize = ProjectileSize(Vector2(41.0f, 41.0f)));
	~Ball();

	// Projectile을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;
	void AddVelocity(Vector2 newVel);
	void SetVelocity(Vector2 vel) { velocity = vel; }
	Vector2 GetVelocity() { return velocity; }

	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;
};