#pragma once
class Projectile :public Transform
{
public:
	class ProjectileSize
	{
	public:
		ProjectileSize(Vector2 size) :size(size) {};
		Vector2 GetSize() const { return size; }
	private:
		Vector2 size;
	};

protected:
	// for drawing
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	// Owner Skill
	Skill* Owner;

	// status
	float damage;
	float speed;
	int maxHitCount;
	int nowHitCount;
	// �ð����� ���� üũ
	float lifeTime;
	float nowTime;

	// �̵��Ÿ��� ���� üũ
	float moveDist;
	float targetDist;

	Collider* collider;
	Vector2 size;

	vector<Collider*> colliders;// �ܰ躰 �浹���� ũ��
	int idx_collider;
	vector<Clip*> clips;// �Ϲ� & Awaken(����)
	// �Ϲ� or Awaken������ �ִϸ��̼��� ���� ��� ���
	int clip_idx;

	// �� �ǰ� ����
	set<Enemy*> hitEnemies;
	list<pair<Enemy*, float>> cooltimeList;
	float hitCoolDown;
	float nowCoolDown;
	int hitLimitCnt;
	vector<Enemy*> enemyNowFrame;
	vector<pair<Enemy*,float>> removeCooltimeList;
	vector<Enemy*> removeList;
	bool isCrt;
	bool isKnockback;

public:
	Vector2 move_dir;

public:
	Projectile(ProjectileSize projSize = ProjectileSize(Vector2()), float damage = 20.0f, float speed = 120.0f, int maxHitCout = 1.0f, float lifeTime = 2.0f, float hitCoolDown = 0.83f);
	virtual ~Projectile();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void OnCollision() = 0;

	virtual void SetStatus(float damage, float speed, int hitCount, float lifeTime,float hitCoolDown=0.83f);
	virtual void SetDirection(Vector2 dir) { move_dir = dir; }
	virtual void respwan() = 0;

	Collider* GetCollider() { return collider; }

	virtual float  GetDamage() { return damage; }

	virtual void Hit()=0;

	void SetColliderIdx(int idx);
	void SetClipIdx(int idx) { clip_idx = idx; }

	int GetRemainHitCnt() { return (maxHitCount - nowHitCount); }

	void SetTargetDist(float dist) { targetDist = dist; }
	float GetTargetDist() { return targetDist; }

	void SetLifeTime(float time) { lifeTime = time; }
	void SetCrt(bool crt) { isCrt = crt; }
	void SetCoolDown(float time) { hitCoolDown = time; }
	void SetHitLimit(int cnt) { hitLimitCnt = cnt; }
	void SetKnockBack(bool knockBack) { isKnockback = knockBack; }
	void SetOwner(Skill* skill) { Owner = skill; }
	Skill* GetOwner() { return Owner; }
};
