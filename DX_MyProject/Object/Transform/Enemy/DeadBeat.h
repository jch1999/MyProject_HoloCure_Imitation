#pragma once
class DeadBeat :public Enemy
{
public:

private:
	Vector2 damageSize, attackSize;
public:
	DeadBeat(ENEMY_NAME name = ENEMY_NAME::DEADBEAT, MOVE_TYPE type = MOVE_TYPE::CHASE, Vector2 damgeSize = Vector2(60.0f, 66.0f), Vector2 attackSize = Vector2(50.0f, 58.0f));
	~DeadBeat();

	// Enemy��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GetDamage(float damage) override;
	virtual void Attack() override;
	virtual void SetEnemyName(ENEMY_NAME name) override;
};