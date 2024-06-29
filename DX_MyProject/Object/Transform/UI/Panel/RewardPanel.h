#pragma once
class RewardPanel :public Panel
{
protected:
	ImageArea* popUp;
	ImageArea* spotLight;
	// ȹ�� ���η� ǥ��
	ImageArea* coinImg;
	TextPrinter* coinText;
	float coinValue, targetCoinValue,increaseSpd;

	RewardBoxAnim* anim;
	float playTime;

	RewardBox* nowBox;
	TextPrinter* openText;
	// ���õ� ��ų ǥ��
	SkillSelector* selector;
	SkillIcon* icon;
	LightEffect* lEffect;
	// ��ų ȹ�� ���� ������
	int seletIdx;
	Button* getBtn, dropBtn;
	
public:
	RewardPanel();
	~RewardPanel();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);
	virtual void SetActive(bool active)override;
	void SetBox(RewardBox* box) { nowBox = box; }
	const RewardBox* GetBox() { return nowBox; }
};