#pragma once
class Coin :public Item
{
protected:
	static vector<shared_ptr<const Frame>>& GetCoinFrames();
	static int& GetCoinUseCnt();

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

	// Item을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::COIN, int value = 0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	virtual void SetPos(Vector2 pos) override;

	virtual void SetAmount(int value) override { coinAmount = value; }
	virtual int GetAmount() override { return coinAmount; }

};