#pragma once
class DeadBeat :public Enemy
{
protected:
	static vector<vector<shared_ptr<const Frame>>> deadBeatFrames;
	static int DeadBestSpawnCnt;

private:
	Vector2 damageSize, attackSize;
public:
	DeadBeat(ENEMY_NAME name = ENEMY_NAME::DEADBEAT, MOVE_TYPE type = MOVE_TYPE::CHASE, Vector2 damgeSize = Vector2(60.0f, 66.0f), Vector2 attackSize = Vector2(50.0f, 58.0f));
	~DeadBeat();

	// Enemy을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetEnemyName(ENEMY_NAME name) override;
};