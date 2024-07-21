#pragma once
class Ball :public Projectile
{
private:

public:
	Ball(Vector2 size = Vector2(41.0f, 41.0f));
	~Ball();

	// Projectile을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;
};