#pragma once
class Panel :public UI
{
protected:
	// Player 이미지를 띄울 이미지
	Icon* player_full_icon;

	// 선택지 번호
	int select_idx;

public:
	Panel();
	~Panel();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
};