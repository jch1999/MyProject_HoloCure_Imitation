#pragma once
class Button :public UI
{
protected:
	TextPrinter* btnText;
public:
	Button();
	virtual ~Button();



	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);

	TextPrinter* GetBtnText() { return btnText; }
};