#pragma once
class KiaraSlash :public Projectile
{
private:

public:
	KiaraSlash(Vector2 size = Vector2(162.5f, 160.0f));
	~KiaraSlash();



	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;
};