#pragma once
class RewardBox :public Item
{
protected:
	static shared_ptr<const Frame>& GetRewardBoxFrame();
	static int& GetRewardBoxUseCnt();

private:
	ItemLight* light;
	int reward_coin;
public:
	RewardBox(Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(24.0f, 26.0f));
	~RewardBox();

	RectCollider* GetCollider() { return collider; }

	// Item을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::ANVIL, int value = 0)override;
	virtual void SetState(ITEM_STATE state);

	virtual void SetPos(Vector2 pos) override;

	virtual void SetAmount(int value) override;
	virtual int GetAmount() override;
};