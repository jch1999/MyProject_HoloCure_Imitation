#pragma once
class PoisonArea :public Projectile
{
protected:
	static shared_ptr<const Frame>& GetPoisonFrame();
	static int& GetPoisonUseCnt();

public:
	PoisonArea(ProjectileSize projSize= ProjectileSize(Vector2(107.0f, 107.0f)));
	~PoisonArea();

	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	virtual void respwan() override;
	virtual void OnCollision() override;
	virtual void Hit() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};