#pragma once
class Skill;
class HPBar;
class ExpBar;
class Arrow;
class Enemy;

class Player :public Transform
{
public:
	enum class PLAYER_ID // 캐릭터 종류 판별
	{
		WATSON,
		KIARA,
		BAELZ
	}player_id;
	enum class PLAYER_STATUS // 캐릭터 상태 판별
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

	vector<shared_ptr<Clip>> clips; // 애니메이션 클립들
	RectCollider* damageCollider; // 피격 판정
	vector<CircleCollider*> pickUpColliders; // 아이템 습득 판정

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
	// Multi-shot Weapon의 추가 발사량 수
	int projCnt;
	// Weapon type별 충돌범위 증가
	int colIdxMelee;
	int colIdxShot;
	int colIdxRange;
	
	float defaultPickUpRange;
	int pickUpRangeIdx;
	
	// 레벨 관련
	int level;
	float nowExp;
	float nowMaxExp;

	float damageDelay; // damage를 받았을 때 그 상태로 머무르는 시간
	float nowDamageDelay;

	// direction
	Vector2 moveDir; // 이동 방향
	Vector2 attackDir; // 투사체 발사 방향

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
	
	// 받은 데미지 처리
	virtual void ChangeHP(float amount, Vector2 dir = Vector2(0, 0), Enemy* causer = nullptr);
	// 공격은 투사체에서 처리하도록 할 예정- 플레이어는 공격력을 전달할 뿐
	//virtual float GetAttack() { return attack; }

	virtual void SetStatus(PLAYER_STATUS newStatus, UINT playOption=0) = 0;
	void SetColor(Float4 color)
	{
		CB->data.colour = color;
	}

	void GetExp(float expValue);
	void SetMaxExp();

	// critical 처리
	bool isCritical();

	// 스테이터스 접근 함수
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

	// 추가 스테이터스 접근
	// Multi-shot Weapon의 추가 발사량 수
	int GetProjCnt() { return projCnt; }
	void SetProjCnt(int cnt);
	// Weapon type별 충돌범위 증가
	int GetColIdxMelee() { return colIdxMelee; }
	void SetColIdxMelee(int idx);
	int GetColIdxShot() { return colIdxShot; }
	void SetColIdxShot(int idx);
	int GetColIdxRange() { return colIdxRange; }
	void SetColIdxRange(int idx);
};