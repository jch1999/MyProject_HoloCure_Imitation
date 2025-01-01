#pragma once
class EnhancePanel :public Panel
{
public:
	enum class ENHANCE_STATE
	{
		START,
		ENHANCING,
		END
	}enhance_state;

public:
	EnhancePanel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = WIN_CENTER);
	~EnhancePanel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetAnvil(Anvil* anvil) { usedAnvil = anvil; }
	Anvil* const GetAnvil() { return usedAnvil; }
	void ChoseSkill();
	void PlayEnhancing();
	void EnhanceEnd();

protected:
	// UPGRADE! �� ���� �ؽ�Ʈ
	TextPrinter* upgradeText;
	// ���� ���� ��ų���� ǥ���� ������ ����Ʈ
	// 0 weaponIcon_list
	// 1 buffIcon_list
	vector<vector<SkillIcon*>> skillIconList;

	Anvil* usedAnvil;
	// ���õ� ��ų�� ������ ����� ������
	SkillSelector* selector;
	// ��ȭ ������ ���� Ȯ����, �Ұ����� ���� �Ұ����� ����(���� ����) ���
	TextPrinter* enhanceRateText;
	ImageArea* coinImg;

	Button* btn;

	// ������ ��ȣ
	// ��ų ������
	int selectIdx;
	bool selected;
	bool isEnhancing;	// ��ȭ ���� - popUpâ�� skill�� Icon, charge effect, ��Ÿ anim �� ���� ����

	ImageArea* popUp;
	SkillIcon* icon;
	TextPrinter* enhanceResultText;
	ChargeEffect* cEffect;
	LightEffect* sEffect;

	Vector2 iconOffset;
	float iconMoveSpd;
	bool isReturning;	// false�̸� icon�� �������� �־���, true�� ���ƿ�
	float moveRot;		// icon�� �̵�����
	float playTime, targetPlayTime;		// �ִϸ��̼� ��� �ð�
	float moveTime, targetMoveTime;		// �̵��ð�, �� ������ȯ ���� �ٽ� 0���� �ʱ�ȭ
};