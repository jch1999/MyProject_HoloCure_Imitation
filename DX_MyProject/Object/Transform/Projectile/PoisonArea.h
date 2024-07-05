#pragma once
class PoisonArea :public Projectile
{
protected:


public:
	PoisonArea();
	~PoisonArea();

	// Projectile을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;
};