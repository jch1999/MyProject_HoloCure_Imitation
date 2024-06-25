#pragma once
class RewardBoxAnim :public UI
{
public :
	enum class BOX_STATE
	{
		FALL,
		CLOSED,
		BOUNCING,
		OPENING,
		OPEN,
	}boxState;
protected:

public:
	RewardBoxAnim();
	~RewardBoxAnim();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void SetState(UI::UI_STATE state);
	void SetAnimState(BOX_STATE bState);
	virtual void SetID(UI::UI_ID id);

};