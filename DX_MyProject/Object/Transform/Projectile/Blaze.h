#pragma once
class Blaze :public Projectile
{
private:
	Vector2 size;
public:
	Blaze(Vector2 size = Vector2(38.0f, 38.0f));
	~Blaze();



	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;
	virtual void Hit() override;
};