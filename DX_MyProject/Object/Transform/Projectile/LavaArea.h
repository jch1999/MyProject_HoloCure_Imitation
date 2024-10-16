#pragma once
class LavaArea : public Projectile
{
public:
	LavaArea(ProjectileSize projSize = ProjectileSize(Vector2()));
	~LavaArea();
protected:
	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void OnCollision() override;

	virtual void respwan() override;

	virtual void Hit() override;

};

