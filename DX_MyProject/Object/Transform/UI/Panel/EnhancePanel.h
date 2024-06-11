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
	// ������ ���� �������� ��� â -- �� ������ ĭ�� ������ ����� �� â�� �ϵ��� ������ ����
	SkillSelector* selector;
	Button* btn;

	// ������ ��ȣ
	// ��ų ������
	int selectIdx;
	bool selected;

public:
	EnhancePanel();
	~EnhancePanel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetAnvil(Anvil* anvil) { usedAnvil = anvil; }
	void ChoseSkill();
};