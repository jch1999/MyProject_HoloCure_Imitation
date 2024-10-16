#pragma once
class KiaraSlash :public Projectile
{
private:
	bool isAwaken;

	// �浹�� Enemy�� �ǰ� Ƚ��
	map<Enemy*, int> enemyHitCount;
public:
	KiaraSlash(ProjectileSize projSize = ProjectileSize(Vector2(162.5f, 160.0f)));
	~KiaraSlash();



	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;
	void SetAwaken(bool awake) { isAwaken = awake; }
};