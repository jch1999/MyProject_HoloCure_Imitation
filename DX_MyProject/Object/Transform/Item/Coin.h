#pragma once
class Coin :public Item
{
private:
	Player* target;

	int coinAmount;
	float speed;
	float idleSPD;
	float nowTime;
	float changeTime;
	bool isUp;

	vector<RectCollider*> colliders;

public:
	Coin();
	~Coin();

	int GetAmount() { return coinAmount; }

	// Item��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::COIN, int value = 0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	// Item��(��) ���� ��ӵ�
	virtual void SetPos(Vector2 pos) override;
};