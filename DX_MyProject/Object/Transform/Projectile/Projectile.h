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
	int colliderIdx;
	vector<shared_ptr<Clip>> clips;// �Ϲ� & Awaken(����)
	// �Ϲ� or Awaken������ �ִϸ��̼��� ���� ��� ���
	int clipIdx;

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
	Vector2 moveDir;

public:
	Projectile(ProjectileSize projSize = ProjectileSize(Vector2()), float damage = 20.0f, float speed = 120.0f, int maxHitCout = 1.0f, float lifeTime = 2.0f, float hitCoolDown = 0.83f);
	virtual ~Projectile();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender();

	virtual void InitFrame();
	virtual void ClearFrame();
	
	virtual void OnCollision() = 0;

	virtual void SetStatus(float inDamage, float inSpeed, int inHitCount, float inLifeTime,float inHitCoolDown=0.83f);
	virtual void SetDirection(Vector2 inDir);
	virtual void respwan() = 0;

	FORCEINLINE Collider* GetCollider() { return collider; }

	virtual float  GetDamage() { return damage; }

	virtual void Hit()=0;

	void SetColliderIdx(int inIdx);
	void SetClipIdx(int inIdx);

	FORCEINLINE int GetRemainHitCnt() { return (maxHitCount - nowHitCount); }

	void SetTargetDist(float inDist);
	FORCEINLINE float GetTargetDist() { return targetDist; }

	void SetLifeTime(float inTime);
	void SetCrt(bool inCrt);
	void SetCoolDown(float inTime);
	void SetHitLimit(int inCnt);
	void SetKnockBack(bool inKnockBack);
	
	void SetOwner(Skill* inSkill);
	FORCEINLINE Skill* GetOwner() { return Owner; }
};
