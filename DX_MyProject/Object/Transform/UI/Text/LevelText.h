#pragma once
class LevelText :public UI
{
protected:

public:
	LevelText();
	~LevelText();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state) override { this->state = state; }
	virtual void SetID(UI::UI_ID id) override;
	void SetClipIdx(int idx);
};