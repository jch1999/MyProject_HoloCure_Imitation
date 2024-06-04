#pragma once
class Count_UI :public UI
{
protected:
	vector<CounterIcon*> counterIcons;
	vector<Text*> coinCnt_text;
	vector<Text*> defeatCnt_text;

	float now_coinCnt, target_coinCnt;
	float now_defeatCnt, target_defeatCnt;
public:
	Count_UI();
	~Count_UI();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);

	void SetClipIdx(int idx) { this->clip_idx = idx; }

	void UpdateCoinCnt();
	void UpdateDefeatCnt();
};