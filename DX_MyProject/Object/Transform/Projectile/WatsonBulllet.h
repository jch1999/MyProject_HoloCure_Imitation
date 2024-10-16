#pragma once
class WatsonBullet :public Projectile
{
private:
	Vector2 size;
	bool isRicochet;
	int ricochetCnt;
public:
	WatsonBullet(ProjectileSize porjSize = ProjectileSize(Vector2(30.0f, 24.0f)));
	~WatsonBullet();



	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;
	virtual void Hit() override;


	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;
	void SetRicochet(bool isRicochet, int cnt) { this->isRicochet = isRicochet; ricochetCnt = cnt; }

};