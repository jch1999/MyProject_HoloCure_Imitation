#pragma once
class BloomGloom :public Enemy
{
protected:
	static vector<vector<shared_ptr<const Frame>>>& GetBloomGloomFrames();
	static int& GetBloomGloomSpawnCnt();

private:
	Vector2 damageSize, attackSize;
public:
	BloomGloom(ENEMY_NAME name = ENEMY_NAME::GLOOM, MOVE_TYPE type = MOVE_TYPE::CHASE, Vector2 damgeSize = Vector2(50.0f, 46.0f), Vector2 attackSize = Vector2(25.0f, 23.0f));
	~BloomGloom();

	// Enemy��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;
	virtual void SetEnemyName(ENEMY_NAME name) override;
};