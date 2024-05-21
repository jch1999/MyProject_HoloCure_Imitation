#pragma once
class CollisionScene :public Scene
{
private:
	RectCollider* player;
	RectCollider* obstacle;
	CircleCollider* circle;

	Missile* m;

public:
	CollisionScene();
	~CollisionScene();

	virtual void Update() override;
	virtual void Render() override;

	// Scene을(를) 통해 상속됨
	virtual void PostRender() override;
};
