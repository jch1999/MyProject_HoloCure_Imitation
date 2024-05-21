#pragma once

class Missile :public Quad
{
private:
	float speed;
	float sleep_time;
	Vector2 size;	// �� ������Ʈ�� ũ�⸦ �����ϴ� �� ����� ��

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