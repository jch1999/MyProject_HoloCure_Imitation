#pragma once
class Text :public UI
{
protected:

public:
	Text();
	~Text();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state) override { this->state = state; }
	virtual void SetID(UI::UI_ID id) override { this->id = id; }
	void SetClipIdx(int idx);
};