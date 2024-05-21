#pragma once
class Investi :public Enemy
{
public:

private:
	Vector2 damageSize, attackSize;
public:
	Investi(ENEMY_NAME name = ENEMY_NAME::INVESTI_GATOR, MOVE_TYPE type = MOVE_TYPE::CHASE, Vector2 damgeSize = Vector2(50.0f, 46.0f), Vector2 attackSize = Vector2(25.0f, 23.0f));
	~Investi();

	// Enemy��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GetDamage(float damage) override;
	virtual void Attack() override;
	virtual void SetEnemyName(ENEMY_NAME name) override;
};