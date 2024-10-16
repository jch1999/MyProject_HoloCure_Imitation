#pragma once
class BaelzDice :public Projectile
{
private:
	bool isRicochet;
	int ricochetCnt;
	
public:
	BaelzDice(ProjectileSize projSize=ProjectileSize(Vector2(36.0f,36.0f)));
	~BaelzDice();



	// Projectile��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void respwan() override;

	virtual void Hit() override;

	// Projectile��(��) ���� ��ӵ�
	virtual void OnCollision() override;
	void SetRicochetInfo(bool isRicochet, int cnt) { this->isRicochet = isRicochet; ricochetCnt = cnt; }
};