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
	bool is_looking_right;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;

	vector<Clip*> clips; // 애니메이션 클립들
	RectCollider* damageCollider; // 피격 판정
	vector<CircleCollider*> pickUpColliders; // 아이템 습득 판정

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
	// Multi-shot Weapon의 추가 발사량 수
	int projCnt;
	// Weapon type별 충돌범위 증가
	int colIdx_Melee;
	int colIdx_Shot;
	int colIdx_Range;
	
	float default_pickUpRange;
	int idx_pickUpRange;
	
	// 레벨 관련
	int level;
	float nowExp;
	float nowMaxExp;

	float damage_delay; // damage를 받았을 때 그 상태로 머무르는 시간
	float now_damage_delay;

	// direction
	Vector2 move_dir; // 이동 방향
	Vector2 attack_dir; // 투사체 발사 방향

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
	
	// 받은 데미지 처리
	virtual void ChangeHP(float amount, Vector2 dir = Vector2(0, 0), Enemy* causer = nullptr);
	// 공격은 투사체에서 처리하도록 할 예정- 플레이어는 공격력을 전달할 뿐
	//virtual float GetAttack() { return attack; }

	virtual void SetStatus(PLAYER_STATUS newStatus, UINT playOption=0) = 0;
	void SetColor(Float4 color)
	{
		CB->data.colour = color;
	}
	void AddClip(Clip* clip) { clips.emplace_back(clip); }

	void GetExp(int expValue);

	// critical 처리
	bool isCritical();

	// 최종 스테이터스 접근
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

	// 추가 스테이터스 접근
	// Multi-shot Weapon의 추가 발사량 수
	int GetProjCnt() { return projCnt; }
	void SetProjCnt(int cnt) { projCnt = cnt; }
	// Weapon type별 충돌범위 증가
	int GetColIdxMelee() { return colIdx_Melee; }
	void SetColIdxMelee(int idx) { colIdx_Melee = idx; }
	int GetColIdxShot() { return colIdx_Shot; }
	void SetColIdxShot(int idx) { colIdx_Shot = idx; }
	int GetColIdxRange() { return colIdx_Range; }
	void SetColIdxRange(int idx) { colIdx_Range = idx; }
};