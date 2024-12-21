#pragma once
class LavaArea : public Projectile
{

private:
	static vector<vector<shared_ptr<const Frame>>> lavaAreaFrames;
	static int lavaAreaUseCnt;

public:
	LavaArea(ProjectileSize projSize = ProjectileSize(Vector2()));
	~LavaArea();
protected:
	// Projectile을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void OnCollision() override;

	virtual void respwan() override;

	virtual void Hit() override;

};

