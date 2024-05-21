#pragma once
class BaelzDice :public Projectile
{
private:
	Vector2 size;
public:
	BaelzDice(Vector2 size=Vector2(36.0f,36.0f));
	~BaelzDice();



	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;
};