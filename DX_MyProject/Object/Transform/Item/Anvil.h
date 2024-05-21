#pragma once
class Anvil :public Item
{
private:
	int useCnt;
	float coolTime; // ���� ����� ����� �� ������, �� �� �����ð� �浹�Ұ� ���°� �ȴ�.
	vector<RectCollider*> colliders;
	RectCollider* collider;

public:
	Anvil(Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(24.0f, 26.0f));
	~Anvil();

	RectCollider* GetCollider() { return collider; }

	void SetUseCnt(int useCnt) { this->useCnt = useCnt; }

	// Item��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::ANVIL, int value = 0)override;

	// Item��(��) ���� ��ӵ�
	virtual void SetPos(Vector2 pos) override;
};