#pragma once
class TextPrinter :public UI
{
protected:
	vector<Text*> textList;
	int lineLength;
	Vector2 charPos;
	Vector2 charScale;
	Vector2 charInterval;
	string printStr;
	int textIdx;
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
	void SetTextInfo(Vector2 cScale, Vector2 cInterval, int len = 40)
	{
		this->charScale = cScale;
		this->charInterval = cInterval;
		this->lineLength = len;
	}
	void SetLineLength(int len) { lineLength = len; }
	void SetCharScale(Vector2 c_scale) { charScale = c_scale; }
	void SetCharInterval(Vector2 interval) { charInterval = interval; }
};