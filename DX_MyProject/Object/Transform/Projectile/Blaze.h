#pragma once
class Blaze :public Projectile
{
private:
	static vector<shared_ptr<const Frame>> blazeFrames;
	static int blazeUseCnt;

public:
	Blaze(ProjectileSize projSize = ProjectileSize(Vector2(38.0f, 38.0f)));
	~Blaze();



	// Projectile을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;
	virtual void Hit() override;

	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;
};