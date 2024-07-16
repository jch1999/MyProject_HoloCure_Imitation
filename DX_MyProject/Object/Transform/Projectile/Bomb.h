#pragma once
class Bomb :public Projectile
{
private:
	Vector2 size;
	float thorwDist;
	Vector2 targetPos;
public:
	Bomb(Vector2 size = Vector2(23.0f, 29.0f), float targetDist = 100.0f, Vector2 move_dir = Vector2(0, 0));
	~Bomb();


	// Projectile을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	void SetTargetPos(Vector2 tPos) { targetPos = tPos; }
};