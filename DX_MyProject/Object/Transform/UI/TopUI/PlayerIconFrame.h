#pragma once
class PlayerIconFrame :public UI
{
protected:
	PlayerIcon* playerIcon;
	HPBar* hpBar;
	HPBar* hpBar_back;
	// 최대 hp가 4자리수가 될 일을 없을 테니 text를 7개(현재 hp 3개, /용 1개, 최대 hp 3개) 만들어 관리
	Vector2 text_startOffset;
	vector<Text*> hpText;
public:
	PlayerIconFrame();
	~PlayerIconFrame();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetHpText();
};