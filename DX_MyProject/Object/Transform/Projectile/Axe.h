#pragma once
class Axe :public Projectile
{
private:

public:
	Axe(Vector2 size=Vector2());
	~Axe();


	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

};