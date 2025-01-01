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
	TextPrinter(Vector2 inSize = Vector2(1.0f, 1.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~TextPrinter();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	virtual void SetID(UI::UI_ID id);
	void SetText(string str);
	void SetTextInfo(Vector2 cScale, Vector2 cInterval, int len = 40);
	void SetLineLength(int inLen);
	void SetCharScale(Vector2 inCScale);
	void SetCharInterval(Vector2 inInterval);
};