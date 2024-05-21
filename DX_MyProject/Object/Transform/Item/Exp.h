#pragma once
class Exp :public Item
{
private:
	Player* target;

	int exp_level; // 경험치의 양에 따라 출력 이미지가 다름
	int exp; // 경험치 량
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

	// Item을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Respawn() override;

	virtual void SetStatus(Item::ITEM_ID id = ITEM_ID::EXP, int value=0)override;
	virtual void SetPlayer(Player* p) { target = p; }

	// Item을(를) 통해 상속됨
	virtual void SetPos(Vector2 pos) override;
};