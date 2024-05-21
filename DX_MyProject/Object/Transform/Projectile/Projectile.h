#pragma once
class Projectile :public Transform
{
public:

protected:
	// for drawing
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

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

	RectCollider* collider;

	vector<RectCollider*> colliders;// �ܰ躰 �浹���� ũ��
	int idx_collider;
	vector<Clip*> clips;// �Ϲ� & Awaken(����)
	// �Ϲ� or Awaken������ �ִϸ��̼��� ���� ��� ���
	int clip_idx;
public:
	Vector2 move_dir;

public:
	Projectile(float damage = 20.0f, float speed = 120.0f, int maxHitCout = 1.0f, float lifeTime = 2.0f);
	virtual ~Projectile();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void SetStatus(float damage, float speed, int hitCount, float lifeTime);
	virtual void SetDirection(Vector2 dir) { move_dir = dir; }
	virtual void respwan() = 0;

	RectCollider* GetCollider() { return collider; }

	virtual float  GetDamage() { return damage; }

	virtual void Hit()=0;

	void SetColliderIdx(int idx);
	void SetClipIdx(int idx) { clip_idx = idx; }

	int GetRemainHitCnt() { return (maxHitCount - nowHitCount); }

	void SetTargetDist(float dist) { targetDist = dist; }
};