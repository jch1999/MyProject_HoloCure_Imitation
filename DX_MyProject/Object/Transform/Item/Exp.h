#pragma once
class Exp :public Item
{
protected:
	static vector<vector<shared_ptr<const Frame>>>& GetExpFrames();
	static int& GetExpUseCnt();

private:
	Player* target;

	int expLevel; // ����ġ�� �翡 ���� ��� �̹����� �ٸ�
	int exp; // ����ġ ��
	float speed;
	float idleSPD;
	float nowTime;
	float changeTime;
	bool isUp;

	vector<RectCollider*> colliders;

public:
	Exp();
	~Exp();

	void SetExp(int expAmount);

	// Item��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::EXP, int value=0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	virtual void SetPos(Vector2 pos) override;

	virtual void SetAmount(int inAmount) override;
	virtual int GetAmount() override { return exp; }

private:
	void SetScale();
};