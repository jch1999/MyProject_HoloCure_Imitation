#pragma once
class Anvil :public Item
{
private:
	int useCnt;
	float coolTime; // 모루는 사용을 취소할 수 있으며, 이 때 일정시간 충돌불가 상태가 된다.
	vector<RectCollider*> colliders;
	RectCollider* collider;

public:
	Anvil(Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(24.0f, 26.0f));
	~Anvil();

	RectCollider* GetCollider() { return collider; }

	void SetUseCnt(int useCnt) { this->useCnt = useCnt; }

	// Item을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::ANVIL, int value = 0)override;

	// Item을(를) 통해 상속됨
	virtual void SetPos(Vector2 pos) override;
};