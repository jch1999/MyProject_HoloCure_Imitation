#pragma once
class RectCollider :public Collider
{
public:
	struct ObbDesc // OBB 충돌 때 사용할,
		// 현재 이 충돌판정이 회전 상황을 반영해서 실제로 계산할 때 이용할 데이터를 정의한 구조체
	{
		Vector2 pos;	// 좌표(=중앙점)
		Vector2 Axis[2];	// 회전된 충돌 판정의 축을 따로 기록해두는 배열
		Vector2 half_size; // 이 회전된 충돌판정의 상하/좌우 크기
	};

private:
	Vector2 size;
	ObbDesc  obb_desc;

	virtual void CreateLine() override;

	bool isAABB(RectCollider* rect, Vector2* overwrap = NULL);
	// AABB 알고리즘으로 사각형 충돌판정과 충돌 여부를 검사하는 함수
	bool isOBB(RectCollider* rect);
	// OBB 알고리즘으로 사각형 충돌판정과 충돌 여부를 검사하는 함수
	bool isAABB(CircleCollider* circle);
	// AABB 알고리즘으로 원형 충돌판정과 충돌 여부를 검사하는 함수
	bool isOBB(CircleCollider* circle);
	// OBB 알고리즘으로 원형 충돌판정과 충돌 여부를 검사하는 함수

	float separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2);
	// OBB 충돌처리의 연산과정 도중 사용할 함수
	// 이 함수는 OBB 알고리즘을 만들 때 구현하면서 설명

public:
	RectCollider(Vector2 size);
	~RectCollider();

	ObbDesc GetObbDesc();	// 호출된 시점에서 이 충돌판정의 회전이 반영된,
	// 실제 충돌판정 데이터를 반환하는 코드
	
	// Collider을(를) 통해 상속됨
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	virtual bool isLineCollision(Vector2 line_start, Vector2 line_end) override;

	Vector2 Size() { return size * GlobalScale(); }
	// 이 충돌판정이 화면 기준으로 실제로 얼마만큼의 사이즈를 가지고 있는지
	// 전체 화면 기준의 길이로 환산해 반환
	
	float RightVX() { return GlobalPos().x + size.x * 0.5f; }
	float LeftVX() { return GlobalPos().x - size.x * 0.5f; }
	float UpVX() { return GlobalPos().y - size.y * 0.5f; }
	float DownVX() { return GlobalPos().y + size.y * 0.5f; }
	// 이상의 4개의 함수들은 AABB 충돌 처리 과정에서 사용되는 함수들
	// 정확히는 이 충돌판정의 상/하/좌/우 각각의 끝자락의 좌표를 계산하는 함수
};

// 자동 생성 단축키 alt + Enter