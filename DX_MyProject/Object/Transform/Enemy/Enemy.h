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
protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	// clip
	vector<Clip*> clips; // �ִϸ��̼� Ŭ���� - ���� �̿ܿ��� �ִϸ��̼��� �ϳ��������� ������ �����ϱ⿡ vector ���

	// collider
	RectCollider* attackCollider;	// ���� ����
	vector<RectCollider*> atkColliders;// Enemy �� ���� ���� - ���� ���̶� �浹ü ũ�Ⱑ �ٸ� �� �����Ƿ�
	RectCollider* damageCollider;	// �ǰ� ����
	vector<RectCollider*> damageColliders;	// Enemy �� �ǰ� ���� - atkCollider���ٴ� Ŀ�� �ϴϱ�
	vector<Vector2> colliderOffset_table;	// Enemy �� ���� ���� offset �� - ����� ��ġ�ϴ� �ͺ��� �ٴڿ� ��ġ�ϵ��� �Ʒ��� �̵�
	int colliderOffset_idx;

	// status
	float MaxHP;
	float HP;
	float attack;
	float spdRate;
	float atk_delay; // �÷��̾ ���� ���� ���� ���ð�
	float atk_nowTime; // ���� �� ��� �ð� üũ��
	int drop_exp;
	vector<int> exp_table; // �� ���� ����ϴ� exp���� �ٸ��� �ƿ� ���̺�� ����� ����

	// ���� ����
	bool is_looking_right;
	float dir_set_delay;

	// ���� �̻� ���� - �� BAD_STATUS�� �ش��ϴ� ���� �ð� ����
	vector<float> badStatus_table;

	// direction
	Vector2 move_dir; // �̵� ����
	Vector2 addtional_dir; // �ܺ� �������� �̵� ������ ���� ����
	
	vector<pair<int,int>> knockbackDir_list;
	vector<float> knockbackTime_list;

	Vector2 dest; // ������ - MOVE_TYPE::CHASE�� �ƴ� ��� ���
	Player* player; // ���� & ���� ���
public:
	Enemy(float MaxHP,float attack,float speed,float atk_dely,int drop_exp);
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	RectCollider* GetAttackCollider() { return attackCollider; }
	RectCollider* GetDamageCollider() { return damageCollider; }

	// ü�� ����
	virtual void ChangeHP(float amount);
	// ������ ��� ������ ��ģ �� ������ GetDamage ȣ��
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