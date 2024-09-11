#pragma once
class WatsonBullet :public Projectile
{
private:
	Vector2 size;
public:
	WatsonBullet(Vector2 size);
	~WatsonBullet();



	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;
	virtual void Hit() override;


	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;

};