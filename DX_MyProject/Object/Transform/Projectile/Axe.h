#pragma once
class Axe :public Projectile
{
private:
	float rotSpeed;
public:
	Axe(Vector2 size = Vector2(46.0f, 46.0f));
	~Axe();


	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;
	void SetRotSpeed(float spd) { rotSpeed = spd; }
	float GetRotSpeed() { return rotSpeed; }
};