#pragma once
class Baelz :public Player
{
private:

public:
	Baelz(float MaxHP = 60.0f, float atk = 11.0f, float speed = 160.0f, float crt = 10.0f, float pickUpRange = 50.0f, float delay = 0.33f, Vector2 size = Vector2(28.8f, 44.0f));
	~Baelz();

	// Player을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetStatus(PLAYER_STATUS newStatus, UINT playOption = 0) override;
};