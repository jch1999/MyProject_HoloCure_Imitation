#pragma once
class PoisonArea :public Projectile
{
protected:
	
public:
	PoisonArea(ProjectileSize projSize= ProjectileSize(Vector2(107.0f, 107.0f)));
	~PoisonArea();

	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void OnCollision() override;
	virtual void Hit() override;
};