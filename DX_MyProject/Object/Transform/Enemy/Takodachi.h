#pragma once
class Takodachi :public Enemy
{
protected:
	static vector<vector<shared_ptr<const Frame>>> takodachiFrames;
	static int takodachiSpawnCnt;

private:
	Vector2 damageSize, attackSize;
public:
	Takodachi(ENEMY_NAME name = ENEMY_NAME::TAKODACHI, MOVE_TYPE type = MOVE_TYPE::CHASE, Vector2 damgeSize = Vector2(46.0f, 46.0f), Vector2 attackSize = Vector2(42.0f, 42.0f));
	~Takodachi();

	// Enemy을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetEnemyName(ENEMY_NAME name) override;
};