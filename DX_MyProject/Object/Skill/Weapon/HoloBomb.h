#pragma once
class HoloBomb :public Weapon
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	vector<Projectile*> explosions;

public:
	HoloBomb();
	~HoloBomb();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateBomb();
	void UpdateBombEffect();
	Bomb* GetBomb();
	Projectile* GetExplosionSmoke();
};