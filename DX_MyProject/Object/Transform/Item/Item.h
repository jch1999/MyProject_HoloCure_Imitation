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

public:
	Item();
	virtual ~Item();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender();
	virtual void Respawn() = 0;
	virtual void InitFrame() = 0;
	virtual void ClearFrame() = 0;

	RectCollider* GetCollider() { return collider; }

	virtual void SetStatus(Item::ITEM_ID id=ITEM_ID::EXP,int value=0) = 0;
	virtual void SetState(ITEM_STATE inState);
	FORCEINLINE const ITEM_STATE& GetState() { return state; }
	virtual void SetPos(Vector2 pos) = 0;
	FORCEINLINE const Vector2& GetPos() { return pos; }
	virtual void SetPlayer(Player *p){}

	void SetAddtionalDir(Vector2 inDir);
	FORCEINLINE const Vector2& GetAddtionalDir() { return addtionalDir; }
	
	virtual void SetAmount(int inAmount) = 0;
	virtual int GetAmount() = 0;

protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;

	vector<shared_ptr<Clip>> clips; // 애니메이션 클립들
	int clipIdx;

	RectCollider* collider;
	Vector2 moveDir;
	Vector2 addtionalDir;
};