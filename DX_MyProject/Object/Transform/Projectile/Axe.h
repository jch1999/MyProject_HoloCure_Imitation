#pragma once
class Axe :public Projectile
{
protected:
	static shared_ptr<const Frame> axeFrame;
	static int axeUseCnt;

private:
	float rotSpeed;
public:
	Axe(ProjectileSize prjSize = ProjectileSize(Vector2(64.0f, 64.0f)));
	~Axe();


	// Projectile을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void OnCollision() override;

	virtual void respwan() override;

	virtual void Hit() override;
	void SetRotSpeed(float spd) { rotSpeed = spd; }
	float GetRotSpeed() { return rotSpeed; }
};