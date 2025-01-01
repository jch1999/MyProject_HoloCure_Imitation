#pragma once
class Anvil :public Item
{
protected:
	static vector<shared_ptr<const Frame>>& GetAnvilFrames();
	static int& GetAnvilSpawnCnt();

private:
	int usableCnt;
	int nowUsedCnt;
	float coolTime; // 모루는 사용을 취소할 수 있으며, 이 때 일정시간 충돌불가 상태가 된다.
	float nowTime;
	shared_ptr<ItemLight> light;

public:
	Anvil(Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(24.0f, 26.0f));
	~Anvil();

	RectCollider* GetCollider() { return collider; }

	void SetUsableCnt(int inUseCnt);

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