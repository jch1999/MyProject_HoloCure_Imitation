#pragma once
class LavaBucket :public Projectile
{

protected:
	static shared_ptr<const Frame>& GetLabaBucketFrame();
	static int& GetLabaBucketUseCnt();

private:
	Projectile* lava;
public:
	LavaBucket(ProjectileSize projSize = ProjectileSize(Vector2(127.0f, 127.0f)));
	~LavaBucket();

	// Projectile을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void respwan() override;
	virtual void Hit() override;

	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};