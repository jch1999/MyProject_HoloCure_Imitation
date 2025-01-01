#pragma once
class Count_UI :public UI
{
protected:
	vector<CounterIcon*> counterIcons;
	vector<Text*> coinCntText;
	vector<Text*> defeatCntText;

	float nowCoinCnt, targetCoinCnt;
	float nowDefeatCnt, targetDefeatCnt;
	float upSpeed;

public:
	Count_UI(Vector2 inSize = Vector2(0.0f, 0.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(WIN_CENTER_X + 150.0f, 50.0f));
	~Count_UI();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void InitFrame() override;

	virtual void ClearFrame() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);

	void SetClipIdx(int idx);

	void UpdateCoinCnt();
	void UpdateDefeatCnt();
};