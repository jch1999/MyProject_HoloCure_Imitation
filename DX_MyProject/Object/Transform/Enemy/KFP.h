#pragma once
class KFP :public Enemy
{
public:

private:
	Vector2 damageSize, attackSize;
public:
	KFP(ENEMY_NAME name = ENEMY_NAME::KFP_EMPLOYEE, MOVE_TYPE type = MOVE_TYPE::STRAIGHT, Vector2 damgeSize = Vector2(50.0f, 46.0f), Vector2 attackSize = Vector2(25.0f, 23.0f));
	~KFP();

	// Enemy을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetEnemyName(ENEMY_NAME name) override;
};