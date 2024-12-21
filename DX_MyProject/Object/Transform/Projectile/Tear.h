#pragma once
class Tear :public Projectile
{
protected:
	static shared_ptr<const Frame> tearFrame;
	static int tearUseCnt;

public:
	Tear(ProjectileSize projSize = ProjectileSize(Vector2(10.0f, 8.0f)));
	~Tear();


	// Projectile��(��) ���� ��ӵ�
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;
};