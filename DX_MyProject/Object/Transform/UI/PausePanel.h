#pragma once
class PausePanel :public UI
{
protected:

public:
	PausePanel();
	~PausePanel();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
};