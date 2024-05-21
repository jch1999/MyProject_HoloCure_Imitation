#pragma once
class Player;
class Item :public Transform
{
public:
	enum class ITEM_TYPE
	{
		EXP,
		ANVIL,
		COIN,
		REWARD_BOX
	}type;
	enum class ITEM_ID
	{
		EXP,
		EXP_MAGNET,
		ANVIL,
		GOLDEN_ANVIL,
		COIN,
		REWORD_BOX
	}id;
	enum class ITEM_STATE
	{
		IDLE,
		ACTIVE,
		USED
	}state;

protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;

	vector<Clip*> clips; // 애니메이션 클립들
	int clip_idx;
	RectCollider* collider;

public:
	Item();
	virtual ~Item();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void Respawn() = 0;

	RectCollider* GetCollider() { return collider; }

	virtual void SetStatus(Item::ITEM_ID id=ITEM_ID::EXP,int value=0) = 0;
	void SetState(ITEM_STATE state) { this->state = state; }
	virtual void SetPos(Vector2 pos) = 0;
	virtual void SetPlayer(Player *p){}
};