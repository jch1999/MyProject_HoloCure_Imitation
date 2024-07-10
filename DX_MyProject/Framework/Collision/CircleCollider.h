#pragma once
class CircleCollider : public Collider
{
private:
	float radius;
	// 사각형 때와는 달리 여기서는 원의 반지름만 계산
	// 1) 당연히 원이니까 원의 크기를 표현하는데 필요한 데이터는 반지름 하나 뿐인 것이 첫째
	// 2) 이 원형 충돌판정에 타원을 만드는 것을 고려한다면 실수 2개로 관리를 해줘야 하나,
	// 타원까지 고려할 경우엔 만드는 난이도가 너무 높아지는 탓에 만들 예정이 없으니
	// 원만 다룬가 가정했기 때문에 반지름만 이용하는 것
	UINT vertex_count;
	// 원을 그릴 때 사용할 정점의 개수를 저장해두는 맴버

	virtual void CreateLine() override;

	bool isAABB(RectCollider* collider);
	bool isOBB(RectCollider* collider);
	// 사각형 충돌판정은 회전을 고려해야 하지만,
	// 원형 충돌판정은 애초에 원이라 회전해도 다 똑같으니 고려할 필요가 없음
	// 그래서 AABB, OBB를 따지는 건 사각형과의 충돌여부를 따질 때만 생각하면 됨

public:
	CircleCollider(float rad);
	~CircleCollider();

	float GetRadius() // 이 충돌판정의 반지름을 구하는 함수
	{
		return radius * min(GlobalScale().x, GlobalScale().y);
	}

	// Collider을(를) 통해 상속됨
	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;

	// Collider을(를) 통해 상속됨
	virtual bool isLineCollision(Vector2 line_start, Vector2 line_end) override;
	virtual Vector2 Size() override { return Vector2(radius * 2.0f, radius * 2.0f) * GlobalScale(); }
};