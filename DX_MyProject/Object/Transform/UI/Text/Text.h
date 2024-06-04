#pragma once
class Text :public UI
{
protected:
	char c;
public:
	Text();
	~Text();

	void SetClipIdx(int idx);
	void SetText(char c);
	void SetSize(char c);

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	Vector2 GetTextSize() { return ui_size * ui_scale; }
};