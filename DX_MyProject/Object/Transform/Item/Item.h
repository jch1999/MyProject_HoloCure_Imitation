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
		REWARD_BOX,
		FOOD
	}type;
	enum class ITEM_ID
	{
		EXP,
		EXP_MAGNET,
		ANVIL,
		GOLDEN_ANVIL,
		COIN,
		REWORD_BOX,
		HAMBURGER
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

	vector<shared_ptr<Clip>> clips; // 애니메이션 클립들
	int clipIdx;
	shared_ptr<const Frame> frame; // 애니메인션 사용하지 않을 경우

	RectCollider* collider;
	Vector2 moveDir;
	Vector2 addtionalDir;

public:
	Item();
	virtual ~Item();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void Respawn() = 0;
	virtual void InitFrame() = 0;
	virtual void ClearFrame() = 0;

	RectCollider* GetCollider() { return collider; }

	virtual void SetStatus(Item::ITEM_ID id=ITEM_ID::EXP,int value=0) = 0;
	virtual void SetState(ITEM_STATE inState);
	virtual void SetPos(Vector2 pos) = 0;
	virtual void SetPlayer(Player *p){}

	Vector2 GetAddtionalDir() { return addtionalDir; }
	void SetAddtionalDir(Vector2 inDir);
	virtual void SetAmount(int value) = 0;
	virtual int GetAmount() = 0;
};