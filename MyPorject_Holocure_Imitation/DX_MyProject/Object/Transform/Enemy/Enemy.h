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
protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	// clip
	vector<Clip*> clips; // 애니메이션 클립들 - 보스 이외에는 애니메이션이 하나뿐이지만 종별로 구현하기에 vector 사용

	// collider
	RectCollider* attackCollider;	// 공격 판정
	vector<RectCollider*> atkColliders;// Enemy 별 공격 판정 - 같은 종이라도 충돌체 크기가 다를 수 있으므로
	RectCollider* damageCollider;	// 피격 판정
	vector<RectCollider*> damageColliders;	// Enemy 별 피격 판정 - atkCollider보다는 커야 하니까
	vector<Vector2> colliderOffset_table;	// Enemy 별 공격 판정 offset 값 - 가운데에 위치하는 것보다 바닥에 위치하도록 아래로 이동
	int colliderOffset_idx;

	// status
	float MaxHP;
	float HP;
	float attack;
	float spdRate;
	float atk_delay; // 플레이어에 대한 공격 판정 대기시간
	float atk_nowTime; // 공격 후 경과 시간 체크용
	int drop_exp;
	vector<int> exp_table; // 종 별로 드랍하는 exp양이 다르니 아예 테이블로 만들어 관리

	// 방향 관련
	bool is_looking_right;
	float dir_set_delay;

	// 상태 이상 관련 - 각 BAD_STATUS에 해당하는 남은 시간 관리
	vector<float> badStatus_table;

	// direction
	Vector2 move_dir; // 이동 방향
	Vector2 addtional_dir; // 외부 영향으로 이동 방향의 변경 정도
	
	vector<pair<int,int>> knockbackDir_list;
	vector<float> knockbackTime_list;

	Vector2 dest; // 목적지 - MOVE_TYPE::CHASE가 아닐 경우 사용
	Player* player; // 공격 & 추적 대상
public:
	Enemy(float MaxHP,float attack,float speed,float atk_dely,int drop_exp);
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	RectCollider* GetAttackCollider() { return attackCollider; }
	RectCollider* GetDamageCollider() { return damageCollider; }

	// 체력 변경
	virtual void ChangeHP(float amount);
	// 데미지 계산 과정을 거친 후 상대방의 GetDamage 호출
	virtual void Attack();

	void SetColor(Float4 color) { CB->data.colour = color; }
	
	void SetMoveDir(Vector2 dir) { move_dir = dir; }
	Vector2 GetMoveDir() { return move_dir; }

	void SetBadStatus(Enemy::BAD_STATUS bad,float time);

	void Move();
	void SetDest(Vector2 dest_pos) { dest = dest_pos; }
	void SetPlayer(Player *target) { player = target; }
	bool IsAttackable() { return atk_nowTime >= atk_delay; }

	void SetStatus(float MaxHP,float atk,float speed,float atk_delay,int drop_exp);
	virtual void SetEnemyName(ENEMY_NAME name) = 0;
	void Respawn();
	void SetAdditionalDirection(Vector2 dir) { addtional_dir = dir; }
	Vector2 GetAddtionalDirection() { return addtional_dir; }
	void SetKnockBack(Vector2 dir, float time);
};