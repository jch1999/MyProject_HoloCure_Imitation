#pragma once

class Missile :public Quad
{
private:
	float speed;
	float sleep_time;
	Vector2 size;	// 이 오브젝트의 크기를 관리하는 데 사용할 값

	RectCollider* collider;
	Transform* target;

protected:

public:
	Missile(Vector2 pos, Vector2 size, Float2 s, float a, Transform* target = NULL);
	~Missile();

	void Update();
	void Render();
	void PostRender();
	RectCollider* GetCollider() { return collider; }

	bool isHit(RectCollider* object);
};