#pragma once
class Blaze :public Projectile
{
private:
	static vector<shared_ptr<const Frame>>& GetBlazeFrames();
	static int& GetBlazeUseCnt();

public:
	Blaze(ProjectileSize projSize = ProjectileSize(Vector2(38.0f, 38.0f)));
	~Blaze();



	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void respwan() override;
	virtual void Hit() override;

	// Projectile을(를) 통해 상속됨
	virtual void OnCollision() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};