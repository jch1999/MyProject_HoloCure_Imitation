#pragma once
class Hambureger :public Item
{
protected:
	static vector<shared_ptr<const Frame>> hambugerFrames;
	static int hambugerUseCnt;

private:
	Player* target;

	int healAmount; // 회복 량
	float speed;
	float idleSPD;
	float nowTime;
	float changeTime;
	bool isUp;

public:
	Hambureger();
	~Hambureger();

	// Item을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;
	
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::EXP, int value = 0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	virtual void SetPos(Vector2 pos) override;

	virtual void SetAmount(int inAmount) override;
	virtual int GetAmount() override { return healAmount; }
};