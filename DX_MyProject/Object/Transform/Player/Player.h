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
	bool is_looking_right;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;

	vector<Clip*> clips; // �ִϸ��̼� Ŭ����
	RectCollider* damageCollider; // �ǰ� ����
	vector<CircleCollider*> pickUpColliders; // ������ ���� ����

	// status
	// default value
	float default_maxHp;
	float default_atk;
	float default_crt;
	float default_spd;
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
	int colIdx_Melee;
	int colIdx_Shot;
	int colIdx_Range;
	
	float default_pickUpRange;
	int idx_pickUpRange;
	
	// ���� ����
	int level;
	float nowExp;
	float nowMaxExp;

	float damage_delay; // damage�� �޾��� �� �� ���·� �ӹ����� �ð�
	float now_damage_delay;

	// direction
	Vector2 move_dir; // �̵� ����
	Vector2 attack_dir; // ����ü �߻� ����

	//UI
	HPBar* hp_bar;
	HPBar* hp_back;
	ExpBar* exp_bar;
	Arrow* atk_arrow;
	
public:
	Player(float MaxHP = 100.0f, float atk = 10.0f, float speed = 100.0f, float crt = 10.0f, float pickupRange = 40.0f, float damage_delay = 0.33f, int idx_pickUpRange = 0,Vector2 size=Vector2(48.0f,60.0f));
	virtual ~Player();

	RectCollider* GetDamageCollider() { return damageCollider; }
	CircleCollider* GetPickUpcollider() { return pickUpColliders[idx_pickUpRange]; }

	virtual void Update() = 0;
	void UpdateDefault();
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	void CheckMoveDir();
	Vector2 GetMoveDir() { return move_dir; }
	Vector2 GetAttackDir() { return attack_dir; }
	
	// ���� ������ ó��
	virtual void ChangeHP(float amount, Vector2 dir = Vector2(0, 0), Enemy* causer = nullptr);
	// ������ ����ü���� ó���ϵ��� �� ����- �÷��̾�� ���ݷ��� ������ ��
	//virtual float GetAttack() { return attack; }

	virtual void SetStatus(PLAYER_STATUS newStatus, UINT playOption=0) = 0;
	void SetColor(Float4 color)
	{
		CB->data.colour = color;
	}
	void AddClip(Clip* clip) { clips.emplace_back(clip); }

	void GetExp(int expValue);

	// critical ó��
	bool isCritical();

	// ���� �������ͽ� ����
	float GetDefaultMaxHP() { return default_maxHp; }
	float GetMaxHP() { return MaxHP; }
	void SetMaxHP(float MaxHp) { this->MaxHP = MaxHp; }
	float GetHP() { return HP; }
	void SetHP(float HP) { this->HP = HP; }
	float GetDefaultAtk() { return default_atk; }
	float GetATK() { return attack; }
	void SetATK(float atk) { this->attack = atk; }
	float GetDefaultSpd() { return default_spd; }
	float GetSPD() { return speed; }
	void SetSPD(float spd) { this->speed = spd; }
	float GetDefaultCrt() { return default_crt; }
	float GetCRT() { return crt; }
	void SetCRT(float crt) { this->crt = crt; }
	int GetPickUpRnage() { return idx_pickUpRange; }
	void SetPickUpRange(int idx) { idx_pickUpRange = idx; }

	float GetMaxExp() { return nowMaxExp; }
	int GetLevel() { return level; }

	// �߰� �������ͽ� ����
	// Multi-shot Weapon�� �߰� �߻緮 ��
	int GetProjCnt() { return projCnt; }
	void SetProjCnt(int cnt) { projCnt = cnt; }
	// Weapon type�� �浹���� ����
	int GetColIdxMelee() { return colIdx_Melee; }
	void SetColIdxMelee(int idx) { colIdx_Melee = idx; }
	int GetColIdxShot() { return colIdx_Shot; }
	void SetColIdxShot(int idx) { colIdx_Shot = idx; }
	int GetColIdxRange() { return colIdx_Range; }
	void SetColIdxRange(int idx) { colIdx_Range = idx; }
};