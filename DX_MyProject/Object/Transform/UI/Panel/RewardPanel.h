#pragma once
class RewardPanel :public UI
{
protected:
	ImageArea* popUp;
	ImageArea* spotLight;
	ImageArea* coinImg;
	TextPrinter* coinText;
	RewardBoxAnim* anim;
	RewardBox* nowBox;

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
};