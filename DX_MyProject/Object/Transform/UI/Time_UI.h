#pragma once
class Time_UI :public UI
{
protected:
	vector<LevelText*> time_text;

public:
	Time_UI();
	~Time_UI();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
};