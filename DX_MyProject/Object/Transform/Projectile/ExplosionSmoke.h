#pragma once
class ExplosionSmoke :public Projectile
{
protected:
	static vector<shared_ptr<const Frame>>& GetExplosionSmokeFrames();
	static int& GetExplosionSmokeUseCnt();

private:
	Vector2 size;
public:
	ExplosionSmoke(ProjectileSize projSize = ProjectileSize(Vector2(128.0f, 128.0f)));
	~ExplosionSmoke();

	// Projectile을(를) 통해 상속됨
	virtual void InitFrame() override;
	virtual void ClearFrame() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void respwan() override;
	virtual void OnCollision() override;
	virtual void Hit() override;

	bool isDamageAble();
};