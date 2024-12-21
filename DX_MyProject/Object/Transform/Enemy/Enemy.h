#pragma once
class Enemy :public Transform
{
public:
	enum class ENEMY_ID
	{
		SHRIMP,
		DEAD_BEAT,
		TAKODACHI,
		KFP,
		INVESTI,
		BLOOM_GLOOM,
		MINI_BOSS,
		BOSS
	}id;
	enum class MOVE_TYPE
	{
		CHASE, // 플레이어 추적형
		WAVE, // 곡선 이동 sin 이동
		STRAIGHT // 직선 이동
	}type;

	enum class ENEMY_NAME
	{
		// Shrimps
		SHRIMP,
		DARKSHRIMP,
		Q_SHRIMP_A,
		Q_SHRIMP_B,
		RIOT_Q_SHRIMP,
		// DeadBeats
		DEADBEAT,
		DEADBATTER,
		Q_DEADBEAT_A,
		Q_DEADBEAT_B,
		RIOT_DEADBEAT,
		RIOT_Q_DEADBEAT,
		// Takodachi
		TAKODACHI,
		HUNGRY_TAKODACHI,
		TAKO_VIKING,
		// KFP
		KFP_EMPLOYEE,
		DISGRUNTLED_EMPLOYEE,
		// Investi
		INVESTI_GATOR,
		THICC_BUBBA,
		// Bloom&Gloom
		BLOOM,
		GLOOM,
		// Mini Boss
		MEGA_SHRIMP,
		TAKO_GRANDE,
		MEGA_DARK_SHRIMP,
		GIANT_DEADBATTER,
		GIANT_Q_DEADBEAT,
		MEGA_Q_SHRIMP
	}name;

	enum class BAD_STATUS
	{
		UPSIDE_DOWN,
		FROZEN,
		HOT,
		END
	};

	struct KnockBackData
	{
		Vector2 knockBackDir;
		float spd;
		float remainTime;
	};

protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	// clip
	vector<shared_ptr<Clip>> clips; // 애니메이션 클립들 - 보스 이외에는 애니메이션이 하나뿐이지만 종별로 구현하기에 vector 사용

	// collider
	RectCollider* attackCollider;	// 공격 판정
	vector<RectCollider*> atkColliders;// Enemy 별 공격 판정 - 같은 종이라도 충돌체 크기가 다를 수 있으므로
	RectCollider* damageCollider;	// 피격 판정
	vector<RectCollider*> damageColliders;	// Enemy 별 피격 판정 - atkCollider보다는 커야 하니까
	vector<Vector2> colliderOffsetTable;	// Enemy 별 공격 판정 offset 값 - 가운데에 위치하는 것보다 바닥에 위치하도록 아래로 이동
	int colliderOffsetIdx;

	// status
	float MaxHP;
	float HP;
	float attack;
	float spdRate;
	float atkDelay; // 플레이어에 대한 공격 판정 대기시간
	float atkNowTime; // 공격 후 경과 시간 체크용
	int dropExp;
	vector<int> expTable; // 종 별로 드랍하는 exp양이 다르니 아예 테이블로 만들어 관리

	// 방향 관련
	bool isLookingRight;
	float dirSetDelay;

	// 상태 이상 관련 - 각 BAD_STATUS에 해당하는 남은 시간 관리
	vector<float> badStatusTable;

	// direction
	Vector2 moveDir; // 이동 방향
	Vector2 addtionalDir; // 외부 영향으로 이동 방향의 변경 정도
	
	//map<pair<int, int>, float> knockback_map;
	list<KnockBackData> knockbackList;

	Vector2 destination; // 목적지 - MOVE_TYPE::CHASE가 아닐 경우 사용
	Player* player; // 공격 & 추적 대상
public:
	Enemy(float inMaxHP, float inAttack, float inSpdRate, float inAtkDelay, int inDropExp);
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void InitFrame() = 0;
	virtual void ClearFrame() = 0;

	FORCEINLINE RectCollider* GetAttackCollider() { return attackCollider; }
	FORCEINLINE RectCollider* GetDamageCollider() { return damageCollider; }

	// 체력 변경
	virtual void ChangeHP(float amount, bool isCrt);
	// 데미지 계산 과정을 거친 후 상대방의 GetDamage 호출
	virtual void Attack();

	void SetColor(Float4 inColor);
	
	void SetMoveDir(Vector2 inDir);
	FORCEINLINE Vector2 GetMoveDir() { return moveDir; }

	void SetBadStatus(Enemy::BAD_STATUS bad,float time);

	void Move();
	void SetDest(Vector2 inDestination);
	void SetPlayer(Player* target);
	
	FORCEINLINE bool IsAttackable() { return atkNowTime >= atkDelay; }

	void SetStatus(float MaxHP,float atk,float speed,float atk_delay,int drop_exp);
	virtual void SetEnemyName(ENEMY_NAME name) = 0;
	void Respawn();
	
	void SetAdditionalDirection(Vector2 inDir);
	FORCEINLINE Vector2 GetAddtionalDirection() { return addtionalDir; }
	
	void SetKnockBack(Vector2 dir, float spd, float time);
	
	FORCEINLINE float GetSpd() { return defaultSPD * spdRate; }
};