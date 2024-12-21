#pragma once
class LavaBucket :public Projectile
{

protected:
	static vector<shared_ptr<const Frame>> labaBucketFrames;
	static int labaBucketUseCnt;
private:
	Projectile* lava;
public:
	LavaBucket(ProjectileSize projSize = ProjectileSize(Vector2(127.0f, 127.0f)));
	~LavaBucket();

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