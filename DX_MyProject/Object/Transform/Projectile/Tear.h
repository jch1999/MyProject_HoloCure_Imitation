#pragma once
class Tear :public Projectile
{
private:

public:
	Tear(Vector2 size = Vector2());
	~Tear();


	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

};