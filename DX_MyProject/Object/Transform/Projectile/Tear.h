#pragma once
class Tear :public Projectile
{
private:

public:
	Tear(Vector2 size = Vector2(10.0f, 8.0f));
	~Tear();


	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;
};