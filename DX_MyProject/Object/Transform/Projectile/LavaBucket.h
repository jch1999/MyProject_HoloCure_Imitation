#pragma once
class LavaBucket :public Projectile
{
private:

public:
	LavaBucket(Vector2 size = Vector2(127.0f, 127.0f));
	~LavaBucket();

	// Projectile을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;
};