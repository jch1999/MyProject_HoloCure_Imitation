#pragma once
class PoisonArea :public Projectile
{
protected:
	Vector2 defaultSize;

public:
	PoisonArea(Vector2 size = Vector2(107.0f, 107.0f));
	~PoisonArea();

	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;
};