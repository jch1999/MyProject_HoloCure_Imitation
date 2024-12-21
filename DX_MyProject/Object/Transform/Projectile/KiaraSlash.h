#pragma once
class KiaraSlash :public Projectile
{
protected:
	static vector<vector<shared_ptr<const Frame>>> slashFrmaes;
	static int slashUseCnt;

private:
	bool isAwaken;

	// �浹�� Enemy�� �ǰ� Ƚ��
	map<Enemy*, int> enemyHitCount;
public:
	KiaraSlash(ProjectileSize projSize = ProjectileSize(Vector2(162.5f, 160.0f)));
	~KiaraSlash();

public:
	// Projectile��(��) ���� ��ӵ�
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;

public:
	void ActiveAwaken();
	void DeactiveAwaken();
};