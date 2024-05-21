#pragma once
class Exp :public Item
{
private:
	Player* target;

	int exp_level; // ����ġ�� �翡 ���� ��� �̹����� �ٸ�
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

	int GetAmount() { return exp; }

	void SetExp(int expAmount);

	// Item��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::EXP, int value=0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	// Item��(��) ���� ��ӵ�
	virtual void SetPos(Vector2 pos) override;
};