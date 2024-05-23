#pragma once
class Hambureger :public Item
{
private:
	Player* target;

	int healAmount; // ȸ�� ��
	float speed;
	float idleSPD;
	float nowTime;
	float changeTime;
	bool isUp;

public:
	Hambureger();
	~Hambureger();

	// Item��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::EXP, int value = 0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	// Item��(��) ���� ��ӵ�
	virtual void SetPos(Vector2 pos) override;

	virtual void SetAmount(int value) override { healAmount=value; }
	virtual int GetAmount() override { return healAmount; }
};