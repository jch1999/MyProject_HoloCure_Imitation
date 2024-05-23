#pragma once
class Shrimp :public Enemy
{
public:

private:
	Vector2 damageSize, attackSize;
public:
	Shrimp(ENEMY_NAME name = ENEMY_NAME::SHRIMP, MOVE_TYPE type = MOVE_TYPE::CHASE, Vector2 damgeSize = Vector2(65.0f, 61.0f), Vector2 attackSize = Vector2(60.0f, 56.0f));
	~Shrimp();

	// Enemy을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetEnemyName(ENEMY_NAME name) override;
};