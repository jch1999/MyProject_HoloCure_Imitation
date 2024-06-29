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
	// 선택된 스킬 표시
	SkillSelector* selector;
	SkillIcon* icon;
	LightEffect* lEffect;
	// 스킬 획득 여부 선택지
	int seletIdx;
	Button* getBtn, dropBtn;
	
public:
	RewardPanel();
	~RewardPanel();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);
	virtual void SetActive(bool active)override;
	void SetBox(RewardBox* box) { nowBox = box; }
	const RewardBox* GetBox() { return nowBox; }
};