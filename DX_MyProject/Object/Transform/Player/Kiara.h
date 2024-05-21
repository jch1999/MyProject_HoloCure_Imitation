#pragma once
class Kiara :public Player
{
private:
	vector<RectCollider*> kiaraCollider;
	vector<Vector2> renderScales;
	vector<Vector2> colliderOffset;

	Vector2 idle_size, move_size;
public:
	Kiara(float MaxHP = 90.0f, float atk = 10.0f, float speed = 140.0f, float crt = 5.0f, float pickUpRange = 50.0f, float delay = 0.33f, Vector2 idle_size = Vector2(32.0f, 44.0f),Vector2 move_size=Vector2(29.6f,42.7f));
	~Kiara();

	// Player을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetStatus(PLAYER_STATUS newStatus, UINT playOption = 0) override;
};