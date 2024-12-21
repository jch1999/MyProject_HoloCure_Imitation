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
		CHASE, // �÷��̾� ������
		WAVE, // � �̵� sin �̵�
		STRAIGHT // ���� �̵�
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
	vector<shared_ptr<Clip>> clips; // �ִϸ��̼� Ŭ���� - ���� �̿ܿ��� �ִϸ��̼��� �ϳ��������� ������ �����ϱ⿡ vector ���

	// collider
	RectCollider* attackCollider;	// ���� ����
	vector<RectCollider*> atkColliders;// Enemy �� ���� ���� - ���� ���̶� �浹ü ũ�Ⱑ �ٸ� �� �����Ƿ�
	RectCollider* damageCollider;	// �ǰ� ����
	vector<RectCollider*> damageColliders;	// Enemy �� �ǰ� ���� - atkCollider���ٴ� Ŀ�� �ϴϱ�
	vector<Vector2> colliderOffsetTable;	// Enemy �� ���� ���� offset �� - ����� ��ġ�ϴ� �ͺ��� �ٴڿ� ��ġ�ϵ��� �Ʒ��� �̵�
	int colliderOffsetIdx;

	// status
	float MaxHP;
	float HP;
	float attack;
	float spdRate;
	float atkDelay; // �÷��̾ ���� ���� ���� ���ð�
	float atkNowTime; // ���� �� ��� �ð� üũ��
	int dropExp;
	vector<int> expTable; // �� ���� ����ϴ� exp���� �ٸ��� �ƿ� ���̺�� ����� ����

	// ���� ����
	bool isLookingRight;
	float dirSetDelay;

	// ���� �̻� ���� - �� BAD_STATUS�� �ش��ϴ� ���� �ð� ����
	vector<float> badStatusTable;

	// direction
	Vector2 moveDir; // �̵� ����
	Vector2 addtionalDir; // �ܺ� �������� �̵� ������ ���� ����
	
	//map<pair<int, int>, float> knockback_map;
	list<KnockBackData> knockbackList;

	Vector2 destination; // ������ - MOVE_TYPE::CHASE�� �ƴ� ��� ���
	Player* player; // ���� & ���� ���
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

	// ü�� ����
	virtual void ChangeHP(float amount, bool isCrt);
	// ������ ��� ������ ��ģ �� ������ GetDamage ȣ��
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