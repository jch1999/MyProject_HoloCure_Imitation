#pragma once
class Text :public UI
{
public:
	Text();
	~Text();

	void SetClipIdx(int idx);
	void SetText(char c);

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	Vector2 GetTextSize() { return ui_size * ui_scale; }

private:
	FORCEINLINE static const Frame* GetTextFrame(const char& c) { return TextFrameMap[c]; }
	FORCEINLINE static const Vector2 GetTextSize(const char& c) { return TextSizeMap[c]; }
	static void Init();
	static void RemoveTextInfo();

protected:
	char c;

private:
	static bool bInit;
	static int TextCnt;
	static unordered_map<char, Frame*> TextFrameMap;
	static unordered_map<char, Vector2> TextSizeMap;
};