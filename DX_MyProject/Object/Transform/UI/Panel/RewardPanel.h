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
	LightEffect* lEffect;

	// ���õ� ��ų ǥ��
	SkillSelector* selector;
	SkillIcon* icon;
	// ��ų ȹ�� ���� ������
	int seletIdx;
	Button* getBtn, *dropBtn;
	
public:
	RewardPanel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(0.0f, 0.0f), Vector2 inOffset = WIN_CENTER);
	~RewardPanel();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void SetID(UI::UI_ID id);
	virtual void SetActive(bool active)override;
	void SetBox(RewardBox* box) { nowBox = box; }
	const RewardBox* GetBox() { return nowBox; }
};