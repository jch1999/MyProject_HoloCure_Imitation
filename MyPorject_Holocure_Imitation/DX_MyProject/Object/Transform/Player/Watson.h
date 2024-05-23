#pragma once
class Watson :public Player
{
private:

public:
	Watson(float MaxHP = 75.0f, float atk = 13.0f, float speed = 135.0f, float crt = 10.0f, float pickUpRange = 50.0f, float delay = 0.33f,Vector2 size=Vector2(24.0f,40.0f));
	~Watson();

	// Player을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetStatus(PLAYER_STATUS newStatus,UINT playOption=0) override;
};