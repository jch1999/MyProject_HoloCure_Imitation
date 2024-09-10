#pragma once
class Axe :public Projectile
{
private:
	float rotSpeed;
public:
	Axe(Vector2 size = Vector2(64.0f, 64.0f));
	~Axe();


	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void OnCollision() override;

	virtual void respwan() override;

	virtual void Hit() override;
	void SetRotSpeed(float spd) { rotSpeed = spd; }
	float GetRotSpeed() { return rotSpeed; }
};