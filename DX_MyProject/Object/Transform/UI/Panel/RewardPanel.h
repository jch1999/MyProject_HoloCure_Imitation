#pragma once
class RewardPanel :public Panel
{
protected:
	ImageArea* popUp;
	ImageArea* spotLight;
	// 획득 코인량 표시
	ImageArea* coinImg;
	TextPrinter* coinText;
	float coinValue, targetCoinValue,increaseSpd;

	RewardBoxAnim* anim;
	float playTime;

	RewardBox* nowBox;
	TextPrinter* openText;
	LightEffect* lEffect;

	// 선택된 스킬 표시
	SkillSelector* selector;
	SkillIcon* icon;
	// 스킬 획득 여부 선택지
	int seletIdx;
	Button* getBtn, *dropBtn;
	
public:
	RewardPanel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(0.0f, 0.0f), Vector2 inOffset = WIN_CENTER);
	~RewardPanel();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void SetID(UI::UI_ID id);
	virtual void SetActive(bool active)override;
	void SetBox(RewardBox* box) { nowBox = box; }
	const RewardBox* GetBox() { return nowBox; }
};