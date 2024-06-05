#pragma once
class TextPrinter :public UI
{
protected:
	vector<Text*> text_list;
	int line_length;
	Vector2 char_pos;
	Vector2 char_scale;
	Vector2 char_interval;
	string printStr;
	int text_idx;
public:
	TextPrinter();
	~TextPrinter();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	void SetText(string str);
	void SetLineLength(int len) { line_length = len; }
	void SetCharScale(Vector2 c_scale) { char_scale = c_scale; }
	void SetCharInterval(Vector2 interval) { char_interval = interval; }
};