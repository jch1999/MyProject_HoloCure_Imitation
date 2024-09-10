#pragma once
class ExplosionSmoke :public Projectile
{
private:
	Vector2 size;
public:
	ExplosionSmoke(Vector2 size = Vector2(128.0f, 128.0f));
	~ExplosionSmoke();

	// Projectile을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void OnCollision() override;
	virtual void Hit() override;

	bool isDamageAble();
};