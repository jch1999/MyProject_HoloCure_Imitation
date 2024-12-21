#pragma once
class ExplosionSmoke :public Projectile
{
protected:
	static vector<shared_ptr<const Frame>> explosionSmokeFrames;
	static int explosionSmokeUseCnt;

private:
	Vector2 size;
public:
	ExplosionSmoke(ProjectileSize projSize = ProjectileSize(Vector2(128.0f, 128.0f)));
	~ExplosionSmoke();

	// Projectile��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void OnCollision() override;
	virtual void Hit() override;

	bool isDamageAble();
};