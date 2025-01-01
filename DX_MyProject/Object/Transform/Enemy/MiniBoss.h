#pragma once
class MiniBoss :public Enemy
{
protected:
	static vector<vector<shared_ptr<const Frame>>>& GetMiniBossFrames();
	static int& GetMiniBossSpawnCnt();

public:
	MiniBoss(ENEMY_NAME name = ENEMY_NAME::DEADBEAT, MOVE_TYPE type = MOVE_TYPE::CHASE);
	~MiniBoss();

	// Enemy��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetEnemyName(ENEMY_NAME name) override;
};