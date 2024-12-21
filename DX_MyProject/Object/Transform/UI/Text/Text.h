#pragma once
class Text :public UI
{
protected:
	char c;

private:
	static int TextUseCnt;
	static unordered_map<char, shared_ptr<const Frame>> TextFrameMap;
	static unordered_map<char, Vector2> TextSizeMap;

public:
	Text();
	~Text();

	void SetClipIdx(int idx);
	void SetText(char c);

	// UI을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	Vector2 GetTextSize();

private:
	FORCEINLINE static shared_ptr<const Frame> GetTextFrame(const char& c) { return TextFrameMap[c]; }
	FORCEINLINE static const Vector2 GetTextSize(const char& c) { return TextSizeMap[c]; }
	static void RemoveTextInfo();
};