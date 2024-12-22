#pragma once
class Text :public UI
{
protected:
	char c;

private:
	static int& GetTextUseCnt();
	static unordered_map<char, shared_ptr<const Frame>>& GetTextFrameMap();
	static unordered_map<char, Vector2>& GetTextSizeMap();

public:
	Text(Vector2 inSize = Vector2(0.0f, 0.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~Text();

	void SetClipIdx(int idx);
	void SetText(char c);

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	Vector2 GetTextSize();

private:
	static void RemoveTextInfo();
};