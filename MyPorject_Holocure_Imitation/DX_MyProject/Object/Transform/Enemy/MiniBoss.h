#pragma once
class MiniBoss :public Enemy
{
public:

private:
	
public:
	MiniBoss(ENEMY_NAME name = ENEMY_NAME::DEADBEAT, MOVE_TYPE type = MOVE_TYPE::CHASE);
	~MiniBoss();

	// Enemy��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetEnemyName(ENEMY_NAME name) override;
};