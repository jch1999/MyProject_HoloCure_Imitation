#pragma once
class EnhancePanel :public Panel
{
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
	SkillIcon* coinIcon;
	Button* btn;

	// ������ ��ȣ
	// ��ų ������
	int selectIdx;
	bool selected;
	bool isEnhancing;	// ��ȭ ���� - popUpâ�� skill�� Icon, charge effect, ��Ÿ anim �� ���� ����
	
	ImageArea* popUp;
	SkillIcon* icon;
	bool isReturning;	// false�̸� icon�� �������� �־���, true�� ���ƿ�
	float moveRot;		// icon�� �̵�����
	float playTime;		// �ִϸ��̼� ��� �ð�

public:
	EnhancePanel();
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
};