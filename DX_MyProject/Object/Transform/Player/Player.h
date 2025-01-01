#pragma once
class Skill;
class HPBar;
class ExpBar;
class Arrow;
class Enemy;

class Player :public Transform
{
public:
	enum class PLAYER_ID // ĳ���� ���� �Ǻ�
	{
		WATSON,
		KIARA,
		BAELZ
	}player_id;
	enum class PLAYER_STATUS // ĳ���� ���� �Ǻ�
	{
		IDLE,
		MOVE
	}action_status;

protected:
	bool isLookingRight;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;

	vector<shared_ptr<Clip>> clips; // �ִϸ��̼� Ŭ����
	RectCollider* damageCollider; // �ǰ� ����
	vector<CircleCollider*> pickUpColliders; // ������ ���� ����

	// status
	// default value
	float defaultMaxHp;
	float defaultAtk;
	float defaultCrt;
	float defaultSpd;
	// now value
	float MaxHP;
	float HP;
	float attack;
	float speed;
	float crt;
	// additional status
	// Multi-shot Weapon�� �߰� �߻緮 ��
	int projCnt;
	// Weapon type�� �浹���� ����
	int colIdxMelee;
	int colIdxShot;
	int colIdxRange;
	
	float defaultPickUpRange;
	int pickUpRangeIdx;
	
	// ���� ����
	int level;
	float nowExp;
	float nowMaxExp;

	float damageDelay; // damage�� �޾��� �� �� ���·� �ӹ����� �ð�
	float nowDamageDelay;

	// direction
	Vector2 moveDir; // �̵� ����
	Vector2 attackDir; // ����ü �߻� ����

	//UI
	HPBar* hp_bar;
	HPBar* hp_back;
	ExpBar* exp_bar;
	Arrow* atk_arrow;
	
public:
	Player(float inMaxHP = 100.0f, float inAtk = 10.0f, float inSpeed = 100.0f, float inCrtRate = 10.0f, float inPickupRange = 40.0f, float inDamageDelay = 0.33f, int inPickUpRangeIdx = 0,Vector2 inSize=Vector2(48.0f,60.0f));
	virtual ~Player();

	RectCollider* GetDamageCollider() { return damageCollider; }
	CircleCollider* GetPickUpcollider() { return pickUpColliders[pickUpRangeIdx]; }

	virtual void Update() = 0;
	void UpdateDefault();
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	void CheckMoveDir();
	Vector2 GetMoveDir() { return moveDir; }
	Vector2 GetAttackDir() { return attackDir; }
	
	// ���� ������ ó��
	virtual void ChangeHP(float amount, Vector2 dir = Vector2(0, 0), Enemy* causer = nullptr);
	// ������ ����ü���� ó���ϵ��� �� ����- �÷��̾�� ���ݷ��� ������ ��
	//virtual float GetAttack() { return attack; }

	virtual void SetStatus(PLAYER_STATUS newStatus, UINT playOption=0) = 0;
	void SetColor(Float4 color)
	{
		CB->data.colour = color;
	}

	void GetExp(float expValue);
	void SetMaxExp();

	// critical ó��
	bool isCritical();

	// �������ͽ� ���� �Լ�
	FORCEINLINE const float GetDefaultMaxHP() const { return defaultMaxHp; }
	FORCEINLINE const float GetMaxHP() { return MaxHP; }
	void SetMaxHP(float inMaxHp);
	
	FORCEINLINE const float GetHP() const { return HP; }
	void IncreaseHp(float inChangeAmount);
	void DecreaseHp(float inChangeAmount);
	
	FORCEINLINE const float GetDefaultAtk() const { return defaultAtk; }
	FORCEINLINE const float GetATK()  { return attack; }
	void SetATK(float inAtk);
	
	FORCEINLINE const float GetDefaultSpd() { return defaultSpd; }
	FORCEINLINE const float GetSPD() { return speed; }
	void SetSPD(float inSpd);
	
	FORCEINLINE const float GetDefaultCrt() const { return defaultCrt; }
	FORCEINLINE const float GetCRT() { return crt; }
	void SetCRT(float crt) { this->crt = crt; }
	
	FORCEINLINE const int GetPickUpRnage() { return pickUpRangeIdx; }
	void SetPickUpRange(int inIdx);
	void IncreasePickUpRange();
	FORCEINLINE const int GetPickUpRangeColNum() { return pickUpColliders.size(); }

	FORCEINLINE float GetMaxExp() { return nowMaxExp; }
	FORCEINLINE int GetLevel() { return level; }

	// �߰� �������ͽ� ����
	// Multi-shot Weapon�� �߰� �߻緮 ��
	int GetProjCnt() { return projCnt; }
	void SetProjCnt(int cnt);
	// Weapon type�� �浹���� ����
	int GetColIdxMelee() { return colIdxMelee; }
	void SetColIdxMelee(int idx);
	int GetColIdxShot() { return colIdxShot; }
	void SetColIdxShot(int idx);
	int GetColIdxRange() { return colIdxRange; }
	void SetColIdxRange(int idx);
};