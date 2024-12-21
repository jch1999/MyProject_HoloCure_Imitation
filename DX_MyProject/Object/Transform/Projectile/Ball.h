#pragma once
class Ball :public Projectile
{
protected:
	static shared_ptr<const Frame> ballFrame;
	static int ballUseCnt;

private:
	Vector2 velocity;

public:
	Ball(ProjectileSize projSize = ProjectileSize(Vector2(41.0f, 41.0f)));
	~Ball();

	// Projectile��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;
	void AddVelocity(Vector2 newVel);
	void SetVelocity(Vector2 vel) { velocity = vel; }
	Vector2 GetVelocity() { return velocity; }

	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;
};