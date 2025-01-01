#pragma once
class Time_UI :public UI
{
protected:
	vector<Text*> stage_text;
	vector<Text*> time_text;

public:
	Time_UI(Vector2 inSize = Vector2(0.0f, 0.0f), Vector2 inScale = Vector2(0.0f, 0.0f), Vector2 inOffset = Vector2(WIN_CENTER_X, 50.0f));
	~Time_UI();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
};