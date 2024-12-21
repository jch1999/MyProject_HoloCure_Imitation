#pragma once
class PoisonArea :public Projectile
{
protected:
	static shared_ptr<const Frame> poisonFrame;
	
public:
	PoisonArea(ProjectileSize projSize= ProjectileSize(Vector2(107.0f, 107.0f)));
	~PoisonArea();

	// Projectile��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void OnCollision() override;
	virtual void Hit() override;
};